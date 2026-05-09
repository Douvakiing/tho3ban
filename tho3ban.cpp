#include "tho3ban.h"
#include "ui_tho3ban.h"
#include "game_window.h"
#include <QIcon>

tho3ban::tho3ban(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tho3ban)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resources/photo.png"));
}

tho3ban::~tho3ban()
{
    delete ui;
}

void tho3ban::on_pushButton_clicked()
{
    // 1. Create a new instance of your game window using 'new'
    // (Note: Check your game_window.h file. Qt usually capitalizes the
    // first letter of the class, so it might be Game_window or game_window)
    game_window *myGame = new game_window();

    // 2. Tell Qt to clean up the memory when this new window is eventually closed
    myGame->setAttribute(Qt::WA_DeleteOnClose);

    // 3. Show the new window
    myGame->show();

    // 4. Hide the main menu
    this->hide();
}


void tho3ban::on_pushButton_2_clicked()
{
    QApplication::quit();
}

