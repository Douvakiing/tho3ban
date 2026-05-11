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
    //builds the game window, prepares the graphics scene, and starts the countdown before play
    explicit game_window(QWidget *parent = nullptr);
    ~game_window();

private slots:
    //advances the game every timer tick and refreshes score, time, and board drawing
    void onGameTick();

    //resets the current round and starts the countdown again
    void on_resetBtn_clicked();

    //stops the game loop and returns from the game screen to the main menu
    void on_backBtn_clicked();

private:
    Ui::game_window *ui;
    //scene contains the board background plus the snake and apple items drawn each frame
    QGraphicsScene *scene;
    
    Game game;

    //colors used to paint the checkerboard background and apple
    const QColor orangeLight{251, 193, 78};
    const QColor orangeDark{252, 178, 79};
    const QColor appleColor{255, 0, 0};

    //board dimensions match the 20x20 logical grid used by the Game class
    int boardCols = 20;
    int boardRows = 20;
    //seconds are counted separately from movement ticks so the snake can move every 100ms
    int secondsElapsed = 0;
    int tickCounter = 0;
    //countdown state is owned by a temporary timer before the main game timer starts
    int countdownValue = 3;
    QTimer *countdownTimer = nullptr;
    void handleCountdownTick();

    //drives the main game loop by calling onGameTick every 100ms after the countdown
    QTimer *gameTimer = nullptr;

    //redraws the scene contents from the current Game state
    void drawGameBoard();
    //builds a crisp checkerboard image and applies it as the scene background brush
    void drawGrid(QColor lightColor, QColor darkColor);
    //draws each snake segment as a one-cell rectangle in scene coordinates
    void drawSnake();
    //draws the apple body and leaf inside the apple's current cell
    void drawApple();
    //scales the 20x20 scene to fit inside the graphics view while keeping its aspect ratio
    void fitBoardToView();
    void updateTimerDisplay();
    //pauses the game, shows 3-2-1-GO, then starts the movement timer
    void roundStartAnimation();

    //keeps the board fitted when the window appears or changes size
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    //captures keyboard input when the main window has focus
    void keyPressEvent(QKeyEvent *event) override;
    //captures keyboard input when the graphics view has focus
    bool eventFilter(QObject *watched, QEvent *event) override;

    //stores the latest accepted direction until the next game tick consumes it
    Direction pendingDirection = Direction::Right;
    //maps arrow keys and WASD keys to snake directions
    bool applyDirectionKey(int key);
};

#endif // GAME_WINDOW_H
