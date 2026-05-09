#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
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

    QVector<QPoint> snake;
    QPoint direction{1, 0};
    int boardCols = 30;
    int boardRows = 30;

    QTimer *gameTimer = nullptr;

    void drawSnake();
    void fitBoardToView();

    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
};

#endif // GAME_WINDOW_H
