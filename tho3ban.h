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
    explicit tho3ban(QWidget *parent = nullptr);
    ~tho3ban() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::tho3ban *ui;
};
#endif // THO3BAN_H
