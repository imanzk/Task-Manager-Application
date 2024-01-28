#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "generics.h"

namespace Ui {
class organization;
}

enum ORGAN{createTeam , creatProject , about , home , teamclick , projectclick , sortteam
,sortproject , filterproject , filterteam};

class organization : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayoutTeam;
    QWidget *scrollWidgetTeam;
    QString filterTeam = "member";
    //
    QVBoxLayout *scrollLayoutProject;
    QWidget *scrollWidgetProject;
    QString filterProject = "member";
signals:
    void _click(ORGAN , Group=Group());
public:
    explicit organization(QWidget *parent = nullptr);
    ~organization();
public:
    void displayTeam(Group);
    void displayProject(Group);
private slots:



    void on_home_clicked();

    void on_about_clicked();

    void on_createTeam_clicked();

    void on_createProject_clicked();

    void on_filterteam_clicked();

    void on_sortteam_clicked();

    void on_filterproject_clicked();

    void on_sortproject_clicked();

private:
    Ui::organization *ui;
};

#endif // ORGANIZATION_H
