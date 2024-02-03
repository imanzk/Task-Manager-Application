#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QTcpSocket>
#include <QStackedWidget>
#include "signuppage.h"
#include "entrancepage.h"
#include "loginpage.h"
#include <QGuiApplication>
#include <QScreen>
#include "recovery.h"
#include <QDir>
#include "home.h"
#include "createorganization.h"
#include <QThread>
#include <QMutex>
#include "organization.h"
#include "createteam.h"
#include "createproject.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "aboutorganization.h"
#include "addmember.h"
#include "membersetting.h"
#include "team.h"
#include "membersettingteam.h"
#include "createtask.h"
#include "task.h"
#include "addcomment.h"
#include "aboutteam.h"
#include "project.h"
#include "aboutproject.h"

namespace admin{
enum com_type{entrance , signup , login , recovery};
enum PLACE{
    null , create_recovery , about_organization , about_project , about_team , archived ,
    create_organization , create_project , create_team , home , member_setting , member_task ,
    organization , project , tasks , team , create_task , add_member , member_setting_team , task ,
    add_comment
};
} using admin::com_type , admin::PLACE;
#define SIZE 3

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTcpSocket* socket;
    QThread thread;
    void repeat();
public:
    PLACE place = PLACE::null;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void run();
private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
signals:
    void newMessage(QString);
public slots:
    void get(QString);
public:
    void send(QString str);
    void create(com_type);
    //
    //to use
    void createRec();
    void createHome();
    void createCreateorgan();
    void createOrgan();
    void createCreateTeam();
    void createCreateProject();
    void createAboutorganization();
    void createAddmember();
    void createMembersetting();
    void createTeam();
    void createMembersettingteam();
    void createCreateTask();
    void createTask();
    void createAddcomment();
    void createAboutTeam();
    void createProject();
    void createAboutProject();
private:
    QWidget *component[SIZE];
    QStackedWidget *stack;
    recovery *rec;
    home *hom;
    createorganization *createorgan;
    organization *organ;
    createteam *createmyteam;
    createproject *createmyproject;
    aboutorganization *aboutorgan;
    addmemberClass *addmemb;
    membersetting *memberset;
    team *myteam;
    membersettingteam* mymembersettingteam;
    createtask *createmytask;
    task *mytask;
    addcomment *addcom;
    aboutteam *aboutmyteam;
    project *myproject;
    aboutproject *aboutmyproject;
private:
    User curUser;
    Organization curOrgan;
    Group curGroup;
    Team curTeam;
    Project curProject;
    User curMember;
    Task curTask;
    QString prevKind;
public slots:
    void entranceFunc(Entrance::key_type type);
    void signupFunc(SignUp::key_type type,User);
    void loginFunc(LogIn::key_type type,User);
    void recFunc(User);
    void homFunc(HOME , Organization);
    void createorganFunc(Organization);
    void organFunc(ORGAN , Group);
    void createteamFunc(Team);
    void createprojectFunc(Project);
    void aboutorganFunc(ABOUTORGAN, Organization);
    void addmemberFunc(ADDMEMBER , User);
    void membersettingFunc(MEMBERSETTING , User);
    void teamFunc(TEAM::t , Team);
    void membersettingteamFunc(MEMBERSETTINGTEAM::t , User);
    void createtaskFunc(Task);
    void taskFunc(TASKPAGE::t , Task);
    void addcommentFunc(QString);
    void aboutteamFunc(ABOUTTEAM::t , Team);
    void projectFunc(PROJECT::t , Project);
    void aboutprojectFunc(ABOUTPROJECT::t , Project);
};


#endif // MAINWINDOW_H
