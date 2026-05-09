#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPoint>
#include <QResizeEvent>
#include <QShowEvent>
#include <QTimer>
#include <QVector>

#include "src/game.h"
#include "src/types.h"

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

    void on_resetBtn_clicked();

    void on_backBtn_clicked();

private:
    Ui::game_window *ui;
    QGraphicsScene *scene;
    
    Game game;

    const QColor orangeLight{251, 193, 78};
    const QColor orangeDark{252, 178, 79};
    const QColor appleColor{255, 0, 0};

    int boardCols = 20;
    int boardRows = 20;
    int secondsElapsed = 0;
    int countdownValue = 3;
    QTimer *countdownTimer = nullptr;
    void handleCountdownTick();

    QTimer *gameTimer = nullptr;

    void drawGameBoard();
    void drawGrid(QColor lightColor, QColor darkColor);
    void drawSnake();
    void drawApple();
    void fitBoardToView();
    void updateTimerDisplay();
    void roundStartAnimation();

    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    Direction pendingDirection = Direction::Right;
    bool applyDirectionKey(int key);
};

#endif // GAME_WINDOW_H
