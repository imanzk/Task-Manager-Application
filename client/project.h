#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include "generics.h"
#include <QVBoxLayout>

namespace Ui {
class project;
}
struct PROJECT{
    enum t{
        back , about , addmember , addtask , memberclick , taskclick
    };
};

class project : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayoutTask;
    QWidget *scrollWidgetTask;
    QVBoxLayout *scrollLayoutMember;
    QWidget *scrollWidgetMember;

public:
    explicit project(QWidget *parent = nullptr);
    ~project();
    Project curProject;
    Organization curOrgan;
    void init();
public:
    void displayMember(User user);
    void displayTask(Task);
signals:
    void _click(PROJECT::t , Project=Project());
private slots:

    void on_back_clicked();

    void on_about_clicked();

    void on_addmember_clicked();

    void on_addtask_clicked();
public slots:
    void on_memberclick();
    void on_taskclick();
private:
    Ui::project *ui;
};

#endif // PROJECT_H
