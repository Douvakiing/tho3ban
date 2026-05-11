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

#include "src/game.h"
#include "src/types.h"
#include "tho3ban.h"

game_window::game_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game_window)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(204, 102, 0)));

    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->installEventFilter(this);
    ui->scoreLabel->setStyleSheet(ui->scorelcdNumber->styleSheet());
    ui->timelcdNumber->display("0:00:00");
    this->setWindowIcon(QIcon(":/resources/photo.png"));
    this->setWindowTitle("Tho3ban++");
     this->setFixedSize(1080,720);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    QGraphicsDropShadowEffect *jojoShadow = new QGraphicsDropShadowEffect();
    jojoShadow->setBlurRadius(0); // Set to 0 for a hard, manga-style outline instead of a soft blur
    jojoShadow->setOffset(6, 6);  // Push the shadow down and to the right for 3D depth
    jojoShadow->setColor(QColor(0x4C1D95)); // Deep "Star Platinum" Purple

    // Apply it to the title
    ui->label->setGraphicsEffect(jojoShadow);

    drawGameBoard();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &game_window::onGameTick);
    roundStartAnimation();
}

game_window::~game_window()
{
    delete ui;
}

void game_window::onGameTick()
{
    // 1. Increment ticks (each tick is 100ms)
    tickCounter++;

    // 2. Only update seconds and UI every 10 ticks (1 second)
    if (tickCounter >= 10) {
        secondsElapsed++;
        tickCounter = 0; // Reset for the next second

        // Update the display only when the second actually changes
        QTime displayTime(0, 0);
        displayTime = displayTime.addSecs(secondsElapsed);
        ui->timelcdNumber->display(displayTime.toString("h:mm:ss"));
    }

    // 3. Move the snake and check game state every tick (keeps movement smooth)
    game.update(pendingDirection);
    ui->scorelcdNumber->display(game.getCurrentScore());
    ui->highScorelcdNumber->display(game.getHighScore());

    if (secondsElapsed >= 359999) { // Limit to 99:59:59 cap
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
    if (!applyDirectionKey(event->key()))
        QMainWindow::keyPressEvent(event);
}

bool game_window::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView && event->type() == QEvent::KeyPress) {
        if (applyDirectionKey(static_cast<QKeyEvent *>(event)->key()))
            return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void game_window::drawGameBoard()
{
    scene->setSceneRect(0, 0, boardCols, boardRows);
    scene->clear();

    drawGrid(orangeLight, orangeDark);
    drawSnake();
    drawApple();

    fitBoardToView();
}

void game_window::drawSnake()
{
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
    // Extract exact X and Y coordinates
    qreal x = apple.getX();
    qreal y = apple.getY();

    // 1. The Apple Body
    // We start slightly offset (x + 0.1, y + 0.2) and make it slightly smaller
    // than 1x1 (width 0.8, height 0.75) so it looks plump and doesn't touch the grid edges.
    QRectF appleBody(x + 0.1, y + 0.2, 0.8, 0.75);

    // Use a bright, piercing Neon Crimson for the apple body
    scene->addEllipse(appleBody, QPen(Qt::NoPen), QBrush(QColor(0xFF0044)));

    // 2. The Leaf
    // We position a tiny green oval near the top right of the apple body
    QRectF appleLeaf(x + 0.45, y + 0.05, 0.3, 0.25);

    // Use a bright Matrix/Neon Green for the leaf
    scene->addEllipse(appleLeaf, QPen(Qt::NoPen), QBrush(QColor(0x39FF14)));
}

void game_window::drawGrid(QColor lightColor, QColor darkColor)
{
    for (int y = 0; y < boardRows; ++y) {
        for (int x = 0; x < boardCols; ++x) {
            const bool light = ((x + y) % 2) == 0;
            scene->addRect(QRectF(x, y, 1, 1), QPen(Qt::NoPen),
                           QBrush(light ? lightColor : darkColor));
        }
    }
}

void game_window::fitBoardToView()
{
    const QRectF board = scene->sceneRect();
    if (!board.isValid() || board.isEmpty())
        return;

    ui->graphicsView->resetTransform();
    ui->graphicsView->fitInView(board, Qt::KeepAspectRatio);
}

void game_window::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    fitBoardToView();
}

void game_window::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    fitBoardToView();
    ui->graphicsView->setFocus(Qt::OtherFocusReason);
}
void game_window::on_resetBtn_clicked()
{
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
    gameTimer->stop();
    tho3ban *mainMenu = new tho3ban();
    this->setAttribute(Qt::WA_DeleteOnClose);
    mainMenu->show();
    this->close();
}
void game_window::roundStartAnimation()
{
    gameTimer->stop(); // Pause the game loop

    // SAFETY CHECK: If a timer already exists (e.g., user clicked Reset twice), kill it.
    if (countdownTimer != nullptr) {
        countdownTimer->stop();
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }

    countdownValue = 3;
    ui->countdownTimeLabel->show();
    ui->countdownTimeLabel->raise();

    // Create and start the new timer
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &game_window::handleCountdownTick);

    handleCountdownTick(); // Trigger '3' immediately
    countdownTimer->start(1000); // 1 second intervals
}

void game_window::handleCountdownTick()
{
    if (countdownValue > 0) {
        ui->countdownTimeLabel->setText(QString::number(countdownValue));
        ui->countdownTimeLabel->setStyleSheet(
            "color: #FF00FF; font-size: 80px; font-weight: bold; background: transparent;"
            );
        countdownValue--;
    }
    else if (countdownValue == 0) {
        ui->countdownTimeLabel->setText("GO!");
        ui->countdownTimeLabel->setStyleSheet(
            "color: #00FFFF; font-size: 80px; font-weight: bold; background: transparent;"
            );
        countdownValue--;

        // Let's speed up the timer so "GO!" disappears faster
        countdownTimer->setInterval(500);
    }
    else {
        // CLEANUP PHASE
        countdownTimer->stop();
        ui->countdownTimeLabel->hide();
        ui->countdownTimeLabel->clear(); // Wipe the text

        // Return focus to the game board so arrow keys work immediately
        ui->graphicsView->setFocus();

        // Start the snake!
        gameTimer->start(100);

        // Safely delete the timer from RAM
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }
}
