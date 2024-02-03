#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QVBoxLayout>
#include "generics.h"

namespace Ui {
class task;
}
struct TASKPAGE{
    enum t{
        edit , remove , addmember , addcomment , back , memberclick , commentclick
    };
};

class task : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayoutMember;
    QWidget *scrollWidgetMember;
    QVBoxLayout *scrollLayoutComment;
    QWidget *scrollWidgetComment;
public:
    Organization curOrgan;
    Task curTask;
    Team curTeam;
    User curUser;
    User curMember;
    QString curComment;
    void init();
    explicit task(QWidget *parent = nullptr);
    ~task();
    void displayUser(User);
    void displayComment(QString);
signals:
    void _click(TASKPAGE::t , Task = Task());
private slots:
    void memberclick();
    void commentclick();
    void on_remove_clicked();

    void on_edit_clicked();

    void on_addmember_clicked();

    void on_addcomment_clicked();

    void on_date_dateTimeChanged(const QDateTime &dateTime);


    void on_back_clicked();

    void on_description_textChanged();

private:
    Ui::task *ui;
};

#endif // TASK_H
