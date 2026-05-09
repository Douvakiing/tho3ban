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

#include "src/game.h"
#include "src/types.h"

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

    drawGameBoard();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &game_window::onGameTick);
    gameTimer->start(100);
}

game_window::~game_window()
{
    delete ui;
}

void game_window::onGameTick()
{
    game.update(pendingDirection);
    ui->lcdNumber->display(game.getCurrentScore());
    if (game.getGameState()) {
        gameTimer->stop();
        gameOverScreen();
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
    const QRectF rect(apple.getX(), apple.getY(), 1, 1);
    scene->addRect(rect, QPen(Qt::NoPen), QBrush(appleColor));
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
void game_window::gameOverScreen()
{
    ui->gameOverFrame->show();
    ui->gameOverFrame->raise();
    ui->label->raise();
    ui->graphicsView->hide();

}