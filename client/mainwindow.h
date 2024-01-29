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



namespace admin{
enum com_type{entrance , signup , login , recovery};
} using admin::com_type;
#define SIZE 3

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTcpSocket* socket;

public:
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
private:
    QWidget *component[SIZE];
    QStackedWidget *stack;
    recovery *rec;
    home *hom;
    createorganization *createorgan;
    organization *organ;
    createteam *createmyteam;
    createproject *createmyproject;
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
};
#endif // MAINWINDOW_H
