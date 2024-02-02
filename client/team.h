#ifndef TEAM_H
#define TEAM_H

#include <QWidget>
#include "generics.h"
#include <QVBoxLayout>
#include <QEvent>
#include <QGraphicsView>
#include <QDropEvent>
#include <QDrag>

namespace Ui {
class team;

}
struct TEAM{
    enum t{
        back , about , addmember , addtask , memberclick , taskclick , memberclicktask
    };
};

class team : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayoutTask;
    QWidget *scrollWidgetTask;
    QVBoxLayout *scrollLayoutMember;
    QWidget *scrollWidgetMember;
public:
    explicit team(QWidget *parent = nullptr);
    ~team();
    Team curTeam;
    Organization curOrg;
    void init();
signals:
    void _click(TEAM::t, Team=Team());
private slots:

    void on_back_clicked();

    void on_about_clicked();

    void on_addmember_clicked();

    void on_addtask_clicked();
public:
    void displayMember(User);
    void displayTask(Task);
public slots:
    void on_memberclick();
    void on_taskclick();
private:
    Ui::team *ui;
};

#endif // TEAM_H
