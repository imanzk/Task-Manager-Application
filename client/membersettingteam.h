#ifndef MEMBERSETTINGTEAM_H
#define MEMBERSETTINGTEAM_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class membersettingteam;
}
struct MEMBERSETTINGTEAM{
    enum t{
        upgrade , disgrade , clear
    };
};

class membersettingteam : public QWidget
{
    Q_OBJECT
    User user;
public:
    explicit membersettingteam(QWidget *parent = nullptr);
    ~membersettingteam();
    void init(User);
private slots:
    void on_upgrade_clicked();

    void on_remove_clicked();
signals:
    void _click(MEMBERSETTINGTEAM::t , User = User());
private:
    Ui::membersettingteam *ui;
};

#endif // MEMBERSETTINGTEAM_H
