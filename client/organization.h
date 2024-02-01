#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "generics.h"

namespace Ui {
class organization;
enum ORGAN{createTeam , creatProject , about , home , teamclick , projectclick , sortteam
             ,sortproject , filterproject , filterteam};
}
using Ui::ORGAN;


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
    QVector<Team> listteam;
    QVector<Project> listproject;
    Team curTeam;
    Project curProject;
public:
    QString filterproject = "all";
    QString filterteam = "all";
    bool sortteam=false;
    bool sortproject=false;
    Organization curOrgan;
    void init();
signals:
    void _click(ORGAN , Group=Group());
public:
    explicit organization(QWidget *parent = nullptr);
    ~organization();
public:
    void display(Team);
    void display(Project);
    void displayTeam(Team);
    void displayProject(Project);
private slots:



    void on_home_clicked();

    void on_about_clicked();

    void on_createTeam_clicked();

    void on_createProject_clicked();

    void on_filterteam_clicked();

    void on_sortteam_clicked();

    void on_filterproject_clicked();

    void on_sortproject_clicked();
public slots:
    void on_teamclick();
    void on_projectclick();
private:
    Ui::organization *ui;
};

#endif // ORGANIZATION_H
