#include "game_window.h"
#include "ui_game_window.h"
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QKeyEvent>
#include <QShowEvent>
#include <QTimer>
#include <QTime>
#include <QGraphicsDropShadowEffect>
#include <QImage>

#include "src/game.h"
#include "src/types.h"
#include "tho3ban.h"

game_window::game_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game_window)
{
    ui->setupUi(this);

    //the graphics view renders a logical 20x20 scene instead of pixel-based board positions
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //the view receives focus and filters key events so movement works while playing
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->installEventFilter(this);
    ui->scoreLabel->setStyleSheet(ui->scorelcdNumber->styleSheet());
    ui->timelcdNumber->display("0:00:00");
    this->setWindowIcon(QIcon(":/resources/photo.png"));
    this->setWindowTitle("Tho3ban++");
     this->setFixedSize(1080,720);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    QGraphicsDropShadowEffect *jojoShadow = new QGraphicsDropShadowEffect();
    jojoShadow->setBlurRadius(0); // makes the title shadow a sharp outline instead of a soft blur
    jojoShadow->setOffset(6, 6);  // moves the shadow down and right to give the title depth
    jojoShadow->setColor(QColor(0x4C1D95)); // uses a dark purple shadow behind the title text

    //attaches the shadow effect to the title label
    ui->label->setGraphicsEffect(jojoShadow);

    //the checkerboard background is drawn once because the board pattern does not change
    scene->setSceneRect(0, 0, boardCols, boardRows);
    drawGrid(orangeLight, orangeDark);

    drawGameBoard();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &game_window::onGameTick);
    //the game loop waits until the countdown finishes before it starts ticking
    roundStartAnimation();
}

game_window::~game_window()
{
    delete ui;
}

void game_window::onGameTick()
{
    //ten movement ticks equal one displayed second because the game timer runs every 100ms
    tickCounter++;

    //the timer display updates only when a full second has passed
    if (tickCounter >= 10) {
        secondsElapsed++;
        tickCounter = 0; // reset the sub-second counter for the next displayed second

        //QTime formats the elapsed seconds into h:mm:ss for the LCD widget
        QTime displayTime(0, 0);
        displayTime = displayTime.addSecs(secondsElapsed);
        ui->timelcdNumber->display(displayTime.toString("h:mm:ss"));
    }

    //each tick applies the most recent direction, moves the snake, and updates scores
    game.update(pendingDirection);
    ui->scorelcdNumber->display(game.getCurrentScore());
    ui->highScorelcdNumber->display(game.getHighScore());

    if (secondsElapsed >= 359999) { // caps the timer display at 99:59:59
        ui->timelcdNumber->display("99:59:59");
    }

    if (game.getGameState()) {
        gameTimer->stop();
        ui->gameOverabel->show();
        ui->gameOverabel->raise();
    } else {
        drawGameBoard();
    }
}

bool game_window::applyDirectionKey(int key)
{
    //arrow keys and WASD share the same direction mapping
    switch (key) {
    case Qt::Key_Left:
    case Qt::Key_A:
        pendingDirection = Direction::Left;
        return true;
    case Qt::Key_Right:
    case Qt::Key_D:
        pendingDirection = Direction::Right;
        return true;
    case Qt::Key_Up:
    case Qt::Key_W:
        pendingDirection = Direction::Up;
        return true;
    case Qt::Key_Down:
    case Qt::Key_S:
        pendingDirection = Direction::Down;
        return true;
    default:
        return false;
    }
}

void game_window::keyPressEvent(QKeyEvent *event)
{
    //handled movement keys are consumed; other keys keep their normal QMainWindow behavior
    if (!applyDirectionKey(event->key()))
        QMainWindow::keyPressEvent(event);
}

bool game_window::eventFilter(QObject *watched, QEvent *event)
{
    //the graphics view can have focus, so its key presses are forwarded to the same mapper
    if (watched == ui->graphicsView && event->type() == QEvent::KeyPress) {
        if (applyDirectionKey(static_cast<QKeyEvent *>(event)->key()))
            return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void game_window::drawGameBoard()
{
    //all moving items are rebuilt from the current Game state while the background brush stays
    scene->setSceneRect(0, 0, boardCols, boardRows);
    scene->clear();


    drawSnake();
    drawApple();

    fitBoardToView();
}

void game_window::drawSnake()
{
    //the snake body is drawn in order so the first segment can use the head color
    for (int i = 0; i < game.getSnake().getSize(); ++i) {
        const Position cell = game.getSnake().getBody()[i];
        const QRectF rect(cell.getX(), cell.getY(), 1, 1);
        const QBrush color = (i == 0) ? QBrush(Qt::green) : QBrush(QColor(0, 180, 0));
        scene->addRect(rect, QPen(Qt::NoPen), color);
    }
}

void game_window::drawApple()
{
    const Position apple = game.getApple().getPosition();
    //scene coordinates match board cells, so the apple's x and y place it directly on the grid
    qreal x = apple.getX();
    qreal y = apple.getY();

    //the body is inset inside the 1x1 cell so it does not touch the checkerboard edges
    QRectF appleBody(x + 0.1, y + 0.2, 0.8, 0.75);

    //the apple body is drawn as an ellipse instead of a full square
    scene->addEllipse(appleBody, QPen(Qt::NoPen), QBrush(QColor(0xFF0044)));

    //the leaf is a smaller ellipse positioned near the apple's top-right edge
    QRectF appleLeaf(x + 0.45, y + 0.05, 0.3, 0.25);

    scene->addEllipse(appleLeaf, QPen(Qt::NoPen), QBrush(QColor(0x39FF14)));
}

void game_window::drawGrid(QColor lightColor, QColor darkColor)
{
    //a higher-resolution image keeps the checkerboard crisp when Qt scales the view
    int cellSize = 30;
    QImage bgImage(boardCols * cellSize, boardRows * cellSize, QImage::Format_RGB32);

    //QPainter fills each image square before the image is converted into a scene brush
    QPainter painter(&bgImage);
    painter.setPen(Qt::NoPen);

    for (int y = 0; y < boardRows; ++y) {
        for (int x = 0; x < boardCols; ++x) {
            const bool light = ((x + y) % 2) == 0;
            painter.setBrush(light ? lightColor : darkColor);
            painter.drawRect(x * cellSize, y * cellSize, cellSize, cellSize);
        }
    }

    //the generated image becomes the scene background brush
    QBrush bgBrush(QPixmap::fromImage(bgImage));

    //the transform maps the 30-pixel image cells back onto the 1-unit scene cells
    QTransform transform;
    transform.scale(1.0 / cellSize, 1.0 / cellSize);
    bgBrush.setTransform(transform);

    //the background survives scene->clear(), so only snake and apple need redrawing each frame
    scene->setBackgroundBrush(bgBrush);
}

void game_window::fitBoardToView()
{
    //invalid scene rectangles are ignored to avoid fitting an empty board
    const QRectF board = scene->sceneRect();
    if (!board.isValid() || board.isEmpty())
        return;

    ui->graphicsView->resetTransform();
    ui->graphicsView->fitInView(board, Qt::KeepAspectRatio);
}

void game_window::resizeEvent(QResizeEvent *event)
{
    //after Qt handles the resize, the board is scaled back into the available view area
    QMainWindow::resizeEvent(event);
    fitBoardToView();
}

void game_window::showEvent(QShowEvent *event)
{
    //when the window first appears, focus is moved to the board so movement keys work
    QMainWindow::showEvent(event);
    fitBoardToView();
    ui->graphicsView->setFocus(Qt::OtherFocusReason);
}
void game_window::on_resetBtn_clicked()
{
    //resetting clears game state, score display, timer display, and restarts the pre-round countdown
    game.resetGame();
    ui->gameOverabel->hide();
    ui->graphicsView->setFocus();
    this->secondsElapsed = 0;
    this->tickCounter = 0;
    ui->scorelcdNumber->display(0);
    ui->timelcdNumber->display("0:00:00");
    roundStartAnimation();
}



void game_window::on_backBtn_clicked()
{
    //leaving the game stops movement, opens a new menu window, and lets Qt delete this window
    gameTimer->stop();
    tho3ban *mainMenu = new tho3ban();
    this->setAttribute(Qt::WA_DeleteOnClose);
    mainMenu->show();
    this->close();
}
void game_window::roundStartAnimation()
{
    gameTimer->stop(); // pause movement while the countdown is visible

    //if reset is clicked during a countdown, the old countdown timer is stopped before making a new one
    if (countdownTimer != nullptr) {
        countdownTimer->stop();
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }

    countdownValue = 3;
    ui->countdownTimeLabel->show();
    ui->countdownTimeLabel->raise();

    //a separate timer controls the countdown text before the main game timer starts
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &game_window::handleCountdownTick);

    handleCountdownTick(); // show 3 immediately instead of waiting one second
    countdownTimer->start(1000); // advance the countdown once per second
}

void game_window::handleCountdownTick()
{
    //positive values show the numeric countdown and then move toward GO
    if (countdownValue > 0) {
        ui->countdownTimeLabel->setText(QString::number(countdownValue));
        ui->countdownTimeLabel->setStyleSheet(
            "color: #FF00FF; font-size: 80px; font-weight: bold; background: transparent;"
            );
        countdownValue--;
    }
    else if (countdownValue == 0) {
        //GO is shown for a shorter interval before actual movement begins
        ui->countdownTimeLabel->setText("GO!");
        ui->countdownTimeLabel->setStyleSheet(
            "color: #00FFFF; font-size: 80px; font-weight: bold; background: transparent;"
            );
        countdownValue--;

        //shorten only the final countdown step
        countdownTimer->setInterval(500);
    }
    else {
        //after GO, hide the label, restore focus, start movement, and release the countdown timer
        countdownTimer->stop();
        ui->countdownTimeLabel->hide();
        ui->countdownTimeLabel->clear(); // remove old countdown text before the next round

        //return focus to the game board so arrow keys work immediately
        ui->graphicsView->setFocus();

        //start the snake movement loop at 100ms per tick
        gameTimer->start(100);

        //Qt deletes the temporary countdown timer after pending events finish
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }
}
