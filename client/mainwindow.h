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

namespace admin{
enum com_type{entrance , signup , login , recovery};
enum PLACE{
    null , create_recovery , about_organization , about_project , about_team , add_member , archived ,
    create_organization , create_project , create_team , home , member_setting , member_task ,
    organization , project , tasks , team
};
} using admin::com_type , admin::PLACE;
#define SIZE 3

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTcpSocket* socket;

public:
    PLACE place = PLACE::null;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
private:
    User curUser;
    Organization curOrgan;
    Group curGroup;
    Team curTeam;
    Project curProject;

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
};

class repeat : public QThread , public MainWindow{
public:
    void run();
};


#endif // MAINWINDOW_H
