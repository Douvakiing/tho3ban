#include "tho3ban.h"
#include "ui_tho3ban.h"

tho3ban::tho3ban(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tho3ban)
{
    ui->setupUi(this);
}

tho3ban::~tho3ban()
{
    delete ui;
}
