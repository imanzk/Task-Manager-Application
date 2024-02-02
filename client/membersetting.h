#ifndef MEMBERSETTING_H
#define MEMBERSETTING_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class membersetting;
enum MEMBERSETTING{
    upgrade , disgrade , clear
};
}using Ui::MEMBERSETTING;

class membersetting : public QWidget
{
    Q_OBJECT
    User user;
public:
    explicit membersetting(QWidget *parent = nullptr);
    ~membersetting();
    void init(User);
signals:
    void _click(MEMBERSETTING , User=User());
private slots:
    void on_upgrade_clicked();

    void on_remove_clicked();

private:
    Ui::membersetting *ui;
};

#endif // MEMBERSETTING_H
