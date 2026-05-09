#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QGraphicsScene>
#include <QPoint>
#include <QResizeEvent>
#include <QShowEvent>
#include <QTimer>
#include <QVector>

namespace Ui {
class game_window;
}

class game_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window();

private slots:
    void onGameTick();

private:
    Ui::game_window *ui;
    QGraphicsScene *scene;

    const QColor orangeLight{251, 193, 78};
    const QColor orangeDark{252, 178, 79};
    const QColor appleColor{255, 0, 0};

    QVector<QPoint> snake;
    QPoint apple;

    QPoint direction{1, 0};
    int boardCols = 20;
    int boardRows = 20;

    QTimer *gameTimer = nullptr;

    void drawGameBoard();
    void drawGrid(QColor lightColor, QColor darkColor);
    void drawSnake();
    void drawApple();
    void fitBoardToView();

    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
};

#endif // GAME_WINDOW_H
