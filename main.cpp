#include "tho3ban.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tho3ban w;
    w.show();
    return QCoreApplication::exec();
}
