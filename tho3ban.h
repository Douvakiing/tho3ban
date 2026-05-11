#ifndef THO3BAN_H
#define THO3BAN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class tho3ban;
}
QT_END_NAMESPACE

class tho3ban : public QMainWindow
{
    Q_OBJECT

public:
    //sets up the main menu window, title, icon, and fixed window behavior
    explicit tho3ban(QWidget *parent = nullptr);
    ~tho3ban() override;

private slots:
    //opens the game window when the play button is clicked
    void on_pushButton_clicked();

    //closes the application when the quit button is clicked
    void on_pushButton_2_clicked();

private:
    //owns the widgets generated from the main menu .ui file
    Ui::tho3ban *ui;
};
#endif // THO3BAN_H
