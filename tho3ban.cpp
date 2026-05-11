#include "tho3ban.h"
#include "ui_tho3ban.h"
#include "game_window.h"
#include <QIcon>

tho3ban::tho3ban(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tho3ban)
{
    //loads widgets from the .ui file and applies the shared window branding
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resources/photo.png"));
    this->setWindowTitle("Tho3ban++");
    this->setFixedSize(1080,720);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

tho3ban::~tho3ban()
{
    //deletes the generated UI object and all child widgets owned by it
    delete ui;
}

void tho3ban::on_pushButton_clicked()
{
    //create the game screen separately so the menu can stay hidden in the background
    game_window *myGame = new game_window();

    //Qt will delete the game window automatically when it closes
    myGame->setAttribute(Qt::WA_DeleteOnClose);

    //show gameplay and hide the menu until the player returns or quits
    myGame->show();

    this->hide();
}


void tho3ban::on_pushButton_2_clicked()
{
    //quit the Qt application from the main menu
    QApplication::quit();
}

