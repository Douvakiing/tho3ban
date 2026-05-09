#include "game_window.h"
#include "ui_game_window.h"
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QShowEvent>
#include <QTimer>

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

    snake = {QPoint(10, 10), QPoint(9, 10), QPoint(8, 10)};
    apple = QPoint(12, 10);
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
    if (snake.isEmpty())
        return;

    QPoint head = snake.front();
    QPoint next = head + direction;

    next.rx() = next.x() % boardCols;
    next.ry() = next.y() % boardRows;

    snake.prepend(next);
    snake.removeLast();

    drawGameBoard();
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
    for (int i = 0; i < snake.size(); ++i) {
        const QPoint cell = snake[i];
        const QRectF rect(cell.x(), cell.y(), 1, 1);
        const QBrush color = (i == 0) ? QBrush(Qt::green) : QBrush(QColor(0, 180, 0));
        scene->addRect(rect, QPen(Qt::NoPen), color);
    }
}

void game_window::drawApple()
{
    scene->addRect(QRectF(apple.x(), apple.y(), 1, 1), QPen(Qt::NoPen), QBrush(appleColor));
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
}