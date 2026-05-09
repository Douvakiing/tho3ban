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
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));

    snake = {QPoint(10, 10), QPoint(9, 10), QPoint(8, 10)};
    drawSnake();

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

    drawSnake();
}

void game_window::drawSnake()
{
    scene->setSceneRect(0, 0, boardCols, boardRows);
    scene->clear();
    scene->addRect(scene->sceneRect(), QPen(Qt::NoPen), QBrush(Qt::black));

    for (int i = 0; i < snake.size(); ++i) {
        const QPoint cell = snake[i];
        const QRectF rect(cell.x(), cell.y(), 1, 1);
        const QBrush color = (i == 0) ? QBrush(Qt::green) : QBrush(QColor(0, 180, 0));
        scene->addRect(rect, QPen(Qt::NoPen), color);
    }

    fitBoardToView();
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