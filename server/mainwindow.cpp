#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refresh()
{
    QSqlQuery q , p;
    //user
    q.prepare("SELECT * FROM organization_member");
    q.exec();
    while(q.next()){
        QString str = q.value("name").toString();
        p.prepare("SELECT * FROM organization WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_member WHERE name='"+str+"'");
            p.exec();
        }
        str = q.value("username").toString();
        p.prepare("SELECT * FROM user WHERE username='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_member WHERE username='"+str+"'");
            p.exec();
        }
    }
    //
    q.prepare("SELECT * FROM organization_project");
    q.exec();
    while(q.next()){
        QString str = q.value("project").toString();
        p.prepare("SELECT * FROM project WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_project WHERE project='"+str+"'");
            p.exec();
        }
        str = q.value("organization").toString();
        p.prepare("SELECT * FROM organization WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_project WHERE organization='"+str+"'");
            p.exec();
        }
    }
    //
    q.prepare("SELECT * FROM organization_team");
    q.exec();
    while(q.next()){
        QString str = q.value("team").toString();
        p.prepare("SELECT * FROM team WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_team WHERE team='"+str+"'");
            p.exec();
        }
        str = q.value("organization").toString();
        p.prepare("SELECT * FROM organization WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM organization_team WHERE organization='"+str+"'");
            p.exec();
        }
    }
    //user
    q.prepare("SELECT * FROM project_member");
    q.exec();
    while(q.next()){
        QString str = q.value("name").toString();
        p.prepare("SELECT * FROM project WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM project_member WHERE name='"+str+"'");
            p.exec();
        }
        str = q.value("username").toString();
        p.prepare("SELECT * FROM user WHERE username='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM project_member WHERE username='"+str+"'");
            p.exec();
        }
    }
    //user
    q.prepare("SELECT * FROM team_member");
    q.exec();
    while(q.next()){
        QString str = q.value("name").toString();
        p.prepare("SELECT * FROM team WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM team_member WHERE name='"+str+"'");
            p.exec();
        }
        str = q.value("username").toString();
        p.prepare("SELECT * FROM user WHERE username='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM team_member WHERE username='"+str+"'");
            p.exec();
        }
    }
    //
    q.prepare("SELECT * FROM project_task");
    q.exec();
    while(q.next()){
        QString str = q.value("project").toString();
        p.prepare("SELECT * FROM project WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM project_task WHERE project='"+str+"'");
            p.exec();
        }
        str = q.value("task").toString();
        p.prepare("SELECT * FROM task WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM project_task WHERE task='"+str+"'");
            p.exec();
        }
    }
    //
    q.prepare("SELECT * FROM team_task");
    q.exec();
    while(q.next()){
        QString str = q.value("team").toString();
        p.prepare("SELECT * FROM team WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM team_task WHERE team='"+str+"'");
            p.exec();
        }
        str = q.value("task").toString();
        p.prepare("SELECT * FROM task WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM team_task WHERE task='"+str+"'");
            p.exec();
        }
    }
    // task_comment
    q.prepare("SELECT * FROM task_comment");
    q.exec();
    while(q.next()){
        QString str = q.value("task").toString();
        p.prepare("SELECT * FROM task WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM task_comment WHERE task='"+str+"'");
            p.exec();
        }
    }
    //user
    q.prepare("SELECT * FROM task_member");
    q.exec();
    while(q.next()){
        QString str = q.value("name").toString();
        p.prepare("SELECT * FROM task WHERE name='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM task_member WHERE name='"+str+"'");
            p.exec();
        }
        str = q.value("username").toString();
        p.prepare("SELECT * FROM user WHERE username='"+str+"'");
        p.exec();
        if(!p.next()){
            p.prepare("DELETE FROM task_member WHERE username='"+str+"'");
            p.exec();
        }
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //sql
    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir;
    QString path = dir.path();
    db.setDatabaseName(path + "db.sqlite");
    if(!db.open())
        qDebug()<<"Error opening database!";
    //db tables
    QSqlQuery query;
    query.prepare("CREATE TABLE user(id integer primary key autoincrement unique not null, name text , email text , password text , username text unique)");
    query.exec();
    query.prepare("CREATE TABLE organization(id integer primary key autoincrement unique not null, name text unique, type text , description text)");
    query.exec();
    query.prepare("CREATE TABLE organization_member(name text, username text , role text)");
    query.exec();
    query.prepare("CREATE TABLE team(id integer primary key autoincrement unique not null, name text unique, department text , description text)");
    query.exec();
    query.prepare("CREATE TABLE project(id integer primary key autoincrement unique not null, name text unique, goal text , description text)");
    query.exec();
    query.prepare("CREATE TABLE organization_team(team text , organization text)");
    query.exec();
    query.prepare("CREATE TABLE organization_project(project text , organization text)");
    query.exec();
    query.prepare("CREATE TABLE team_member(name text ,username text, role text)");
    query.exec();
    query.prepare("CREATE TABLE project_member(name text ,username text, role text)");
    query.exec();
    query.prepare("CREATE TABLE task(id integer primary key autoincrement unique not null, name text unique, date text , description text)");
    query.exec();
    query.prepare("CREATE TABLE team_task(task text, team text)");
    query.exec();
    query.prepare("CREATE TABLE task_member(name text, username text)");
    query.exec();
    query.prepare("CREATE TABLE task_comment(task text, comment text)");
    query.exec();
    query.prepare("CREATE TABLE project_task(project text, task text)");
    query.exec();
    //
    //server
    server = new QTcpServer();
    connect(this , &MainWindow::newMessage , this , &MainWindow::get);
    if(server->listen(QHostAddress::LocalHost, 8080))
    {
        qDebug() << "server is listening..";
        connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
    }
    else
    {
        qDebug("Unable to start the server");
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow() {
    db.close();
    foreach (QTcpSocket *memb, connections)
    {
        memb->close();
        memb->deleteLater();
    }

    server->close();
    server->deleteLater();
}


void MainWindow::newConnection()
{
    while (server->hasPendingConnections()){
        appendToSocketList(server->nextPendingConnection());
    }
}

void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connections.push_back(socket);
    qDebug() << "new connection";
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);
}

void MainWindow::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    emit newMessage(socket->readAll() , socket);
}

void MainWindow::discardSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    qDebug() << "disconnected";
    for(int i = 0; i < connections.size() ; i++){
        if(connections[i] == socket){
            connections.erase(connections.begin() + i);
            break;
        }
    }
    socket->deleteLater();
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug("The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug("The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
    default:
        qDebug("Unknown Error!");
        break;
    }
}

void MainWindow::send(QString str , QTcpSocket* socket)
{
    qDebug()<<"send:"<<str;
    if(socket)
        sendMessage(socket , str);
    else {
        for(auto x:connections){
            sendMessage(x , str);
        }
    }
}

void MainWindow::sendMessage(QTcpSocket* socket , QString str)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = str.toUtf8();
            byteArray.prepend(header);

            socketStream.setVersion(QDataStream::Qt_5_15);
            socketStream << byteArray;
        }
        else
            qDebug("Socket doesn't seem to be opened");
    }
    else
        qDebug("Not connected");
}

void MainWindow::get(QString str , QTcpSocket* socket)
{
    refresh();
    refresh();
    refresh();
    qDebug() << "get:" << str;
    QSqlQuery qry;
    QSqlQuery qry2;
    int in = str.indexOf(" ") + 1;
    //signup
    if(str.split(" ").at(0) == "INSERT"){
        qry.prepare(str);
        if(!qry.exec()){
            send("username exists",socket);
        }
        else {
            send("user was added",socket);
        }
    }
    //login
    else if(str.split(" ").at(0) == "SELECT"){
        qry.prepare(str);
        qry.exec();
        if(!qry.next()){
            send("wrong information",socket);
        }
        else {
            send("user was recognized",socket);
        }
    }
    //recovery
    else if(str.split(" ").at(0) == "recovery"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        if(!qry.next()){
            send("rec wrong email or username",socket);
        }
        else{
            QString pas = qry.value(0).toString();
            send("passwordRec "+pas,socket);
        }
    }
    //createorgan
    else if(str.split(" ").at(0) == "org"){
        str.remove(0,in);
        if(str.split(" ").at(0) == "INSERT"){
            qry.prepare(str);
            if(!qry.exec()){
                send("organization name exists",socket);
            }else{
                send("organization was added",socket);
            }
        }
        else {
            QStringList l = str.split(" ");
            qry.prepare("INSERT INTO 'organization_member' (username, name, role) VALUES ('"+l[0]+"','"+l[1]+"','manager')");
            qry.exec();
        }
    }
    //client
    else if(str.split(" ").at(0) == "client"){
        // str.remove(0 , 7);
        // connections.insert(str,socket);
        // qDebug() << "connected as " << str;
    }
    //home
    else if(str.split(" ").at(0) == "home"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        //
        QString q = "home";
        QString name;
        QString role;
        while(qry.next()){
            name = qry.value("name").toString();
            role = qry.value("role").toString();
            q = q + " " + name + " " + role;
        }
        send(q,socket);
    }
    //team
    else if(str.split(" ").at(0) == "team"){
        str.remove(0,in);
        if(str.split(" ").at(0) == "INSERT"){
            qry.prepare(str);
            if(!qry.exec()){
                send("team name exists",socket);
            }else{
                send("team was added",socket);
            }
        }
        else {
            QStringList l = str.split(" ");
            qry.prepare("INSERT INTO 'organization_team' (team, organization) VALUES ('"+l[0]+"','"+l[1]+"')");
            qry.exec();
        }
    }
    //project
    else if(str.split(" ").at(0) == "project"){
        str.remove(0,8);
        if(str.split(" ").at(0) == "INSERT"){
            qry.prepare(str);
            if(!qry.exec()){
                send("project name exists",socket);
            }else{
                send("project was added",socket);
            }
        }
        else {
            QStringList l = str.split(" ");
            qry.prepare("INSERT INTO 'organization_project' (project, organization) VALUES ('"+l[0]+"','"+l[1]+"')");
            qry.exec();
        }
    }
    //createtask
    else if(str.split(" ").at(0) == "createtask"){
        str.remove(0,in);
        if(str.split(" ").at(0) == "INSERT"){
            qry.prepare(str);
            if(!qry.exec()){
                send("task name exists",socket);
            }else{
                send("task was added",socket);
            }
        }
        else {
            str.remove(0,4);
            qry.prepare(str);
            qry.exec();
        }
    }
    //getteam
    else if(str.split(" ").at(0) == "getteam"){
        str.remove(0,in);
        QString username = str.split(" ").at(0);
        str.remove(0,str.indexOf(" "));
        qry.prepare(str);
        qry.exec();
        //
        QString q = "getteam";
        QString team;
        while(qry.next()){
            team = qry.value("team").toString();
            qry2.prepare("SELECT * FROM team_member WHERE name='"+team+"' AND username='"+username+"'");
            qry2.exec();
            char exist = '1';
            if(!qry2.next()) exist = '0';
            q = q + " " + team + " " + exist;
        }
        send(q,socket);
    }
    //getproject
    else if(str.split(" ").at(0) == "getproject"){
        str.remove(0, in);
        QString username = str.split(" ").at(0);
        str.remove(0,str.indexOf(" "));
        qry.prepare(str);
        qry.exec();
        //
        QString q = "getproject";
        QString project;
        while(qry.next()){
            project = qry.value("project").toString();
            qry2.prepare("SELECT * FROM project_member WHERE name='"+project+"' AND username='"+username+"'");
            qry2.exec();
            char exist = '1';
            if(!qry2.next()) exist = '0';
            q = q + " " + project + " " + exist;
        }
        send(q,socket);
    }
    //getmemberorg
    else if(str.split(" ").at(0) == "getmemberorg"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        //
        QString q = "getmemberorg";
        QString member;
        while(qry.next()){
            member = qry.value("username").toString();
            member = member + " " + qry.value("role").toString();
            q = q + " " + member;
        }
        send(q,socket);
    }
    //editorgan
    else if(str.split(" ").at(0) == "editorgan"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        //
        send("editorgan",socket);
    }
    //getrole
    else if(str.split(" ").at(0) == "getrole"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        qry.next();
        send("getrole "+qry.value("role").toString(),socket);
    }
    //curorgan
    else if(str.split(" ").at(0) == "curorgan"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        qry.next();
        QString name = qry.value("name").toString();
        QString type = qry.value("type").toString();
        QString description = qry.value("description").toString();
        send("curorgan " + name +"," + type + "," + description , socket);
    }
    //removeorgan
    else if(str.split(" ").at(0) == "removeorgan"){
        str.remove(0,in);
        qry.prepare("DELETE FROM organization WHERE name='"+str+"'");
        qry.exec();
        qry.prepare("DELETE FROM 'organization_member' WHERE name='"+str+"'");
        qry.exec();
        //
        qry.prepare("SELECT * FROM 'organization_team' WHERE organization='"+str+"'");
        qry.exec();
        while(qry.next()){
            QString team = qry.value("team").toString();
            QSqlQuery qry2;
            qry2.prepare("DELETE FROM team WHERE name='"+team+"'");
            qry2.exec();
        }
        qry.prepare("SELECT * FROM 'organization_project' WHERE organization='"+str+"'");
        qry.exec();
        while(qry.next()){
            QString project = qry.value("project").toString();
            QSqlQuery qry2;
            qry2.prepare("DELETE FROM project WHERE name='"+project+"'");
            qry2.exec();
        }
        qry.prepare("DELETE FROM 'organization_project' WHERE organization='"+str+"'");
        qry.exec();
        qry.prepare("DELETE FROM 'organization_team' WHERE organization='"+str+"'");
        qry.exec();
        send("removeorgan "+str);
    }
    //addmember
    else if(str.split(" ").at(0) == "addmember"){
        str.remove(0 , in);
        qry.prepare(str);
        qry.exec();
        send("addmember" ,socket);
    }
    //searchmember
    else if(str.split(" ").at(0) == "searchmember"){
        str.remove(0,in);
        QStringList l = str.split(" ");
        qry.prepare("SELECT * FROM user WHERE username LIKE '"+l[0]+"%'");
        qry.exec();
        QString q = "searchmember";
        while(qry.next()){
            QSqlQuery qry2;
            QString username = qry.value("username").toString();
            QString name = l[1];
            qry2.prepare("SELECT * FROM 'organization_member' WHERE username='"+username+"' AND name='"+name+"'");
            qry2.exec();
            if(qry2.next()) continue;
            else {
                q = q + " " + username;
            }
        }
        send(q , socket);
    }
    //addmemberteam
    else if(str.split(" ").at(0) == "addmemberteam"){
        str.remove(0 , in);
        qry.prepare(str);
        qry.exec();
        send("addmember" ,socket);
    }
    //searchmemberteam
    else if(str.split(" ").at(0) == "searchmemberteam"){
        str.remove(0,in);
        QStringList l = str.split(" ");
        qry.prepare("SELECT * FROM 'organization_member' WHERE name='"+l[2]+"' AND username LIKE '"+l[0]+"%'");
        qry.exec();
        QString q = "searchmember";
        while(qry.next()){
            QSqlQuery qry2;
            QString username = qry.value("username").toString();
            QString name = l[1];
            qry2.prepare("SELECT * FROM 'team_member' WHERE username='"+username+"' AND name='"+name+"'");
            qry2.exec();
            if(qry2.next()) continue;
            else {
                q = q + " " + username;
            }
        }
        send(q , socket);
    }
    //addmemberproject
    else if(str.split(" ").at(0) == "addmemberproject"){
        str.remove(0 , in);
        qry.prepare(str);
        qry.exec();
        send("addmember" ,socket);
    }
    //searchmemberproject
    else if(str.split(" ").at(0) == "searchmemberproject"){
        str.remove(0,in);
        QStringList l = str.split(" ");
        qry.prepare("SELECT * FROM 'organization_member' WHERE name='"+l[2]+"' AND username LIKE '"+l[0]+"%'");
        qry.exec();
        QString q = "searchmember";
        while(qry.next()){
            QSqlQuery qry2;
            QString username = qry.value("username").toString();
            QString name = l[1];
            qry2.prepare("SELECT * FROM 'project_member' WHERE username='"+username+"' AND name='"+name+"'");
            qry2.exec();
            if(qry2.next()) continue;
            else {
                q = q + " " + username;
            }
        }
        send(q , socket);
    }
    //addmembertask
    else if(str.split(" ").at(0) == "addmembertask"){
        str.remove(0 , in);
        qry.prepare(str);
        qry.exec();
        send("addmember" ,socket);
    }
    //searchmembertask
    else if(str.split(" ").at(0) == "searchmembertask"){
        str.remove(0,in);
        QStringList l = str.split(" ");
        qry.prepare("SELECT * FROM 'organization_member' WHERE name='"+l[2]+"' AND username LIKE '"+l[0]+"%'");
        qry.exec();
        QString q = "searchmember";
        while(qry.next()){
            QSqlQuery qry2;
            QString username = qry.value("username").toString();
            QString name = l[1];
            qry2.prepare("SELECT * FROM 'task_member' WHERE username='"+username+"' AND name='"+name+"'");
            qry2.exec();
            if(qry2.next()) continue;
            else {
                q = q + " " + username;
            }
        }
        send(q , socket);
    }
    //membersetting
    else if(str.split(" ").at(0) == "membersetting"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("membersetting" ,socket);
    }
    //membersettingteam
    else if(str.split(" ").at(0) == "membersettingteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("membersettingteam",socket);
    }
    //getmemberteam
    else if(str.split(" ").at(0) == "getmemberteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "getmemberteam";
        while(qry.next()){
            QString username = qry.value("username").toString();
            QString role = qry.value("role").toString();
            q = q + " " + username + " " + role;
        }
        send(q,socket);
    }
    //gettaskteam
    else if(str.split(" ").at(0) == "gettaskteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "gettaskteam";
        while(qry.next()){
            QString taskname = qry.value("task").toString();
            q = q + " " + taskname;
        }
        send(q,socket);
    }
    //gettaskproject
    else if(str.split(" ").at(0) == "gettaskproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "gettaskproject";
        while(qry.next()){
            QString taskname = qry.value("task").toString();
            q = q + " " + taskname;
        }
        send(q,socket);
    }
    //curteam
    else if(str.split(" ").at(0) == "curteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "curteam";
        if(!qry.next()){
            send("curteam member doesn't exist",socket);
            return;
        }
        QString username = qry.value("username").toString();
        QString name = qry.value("name").toString();
        QString role = qry.value("role").toString();
        q = q + " " +username+ " " + name + " " + role;
        send(q,socket);
    }
    //curtask
    else if(str.split(" ").at(0) == "curtask"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "curtask";
        qry.next();
        QString description = qry.value("description").toString();
        QString name = qry.value("name").toString();
        QString date = qry.value("date").toString();
        q = q + " " + name + "," + date + "," + description;
        send(q,socket);
    }
    //gettaskmember
    else if(str.split(" ").at(0) == "gettaskmember"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "gettaskmember";
        while(qry.next()){
            QString username = qry.value("username").toString();
            q = q + " " + username;
        }
        send(q,socket);
    }
    //gettaskcomment
    else if(str.split(" ").at(0) == "gettaskcomment"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q = "gettaskcomment ";
        while(qry.next())
        {
            QString comment = qry.value("comment").toString();
            q = q + "," + comment;
        }
        send(q,socket);
    }
    //addcomment
    else if(str.split(" ").at(0) == "addcomment"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
    }
    //removecomment || removemembertask
    else if(str.split(" ").at(0) == "removecomment"
             || str.split(" ").at(0) == "removemembertask"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
    }
    //edittask
    else if(str.split(" ").at(0) == "edittask"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
    }
    //removetask
    else if(str.split(" ").at(0) == "removetask"){
        str.remove(0,in);
        QString task = str;
        qry.prepare("DELETE FROM task WHERE name='"+task+"'");
        qry.exec();
        qry.prepare("DELETE FROM task_member WHERE name='"+task+"'");
        qry.exec();
        qry.prepare("DELETE FROM team_task WHERE task='"+task+"'");
        qry.exec();
        qry.prepare("DELETE FROM project_task WHERE task='"+task+"'");
        qry.exec();
    }
    //removeteam
    else if(str.split(" ").at(0) == "removeteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("removeteam" , socket);
    }
    //removeproject
    else if(str.split(" ").at(0) == "removeproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("removeproject" , socket);
    }
    //editteam
    else if(str.split(" ").at(0) == "editteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("editteam" , socket);
    }
    //editproject
    else if(str.split(" ").at(0) == "editproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("editproject" , socket);
    }
    //getaboutteam
    else if(str.split(" ").at(0) == "getaboutteam"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        qry.next();
        QString name = qry.value("name").toString();
        QString department = qry.value("department").toString();
        QString description = qry.value("description").toString();
        QString q = "getaboutteam " + name + "," + department + "," + description;
        send(q , socket);
    }
    //getaboutproject
    else if(str.split(" ").at(0) == "getaboutproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        qry.next();
        QString name = qry.value("name").toString();
        QString goal = qry.value("goal").toString();
        QString description = qry.value("description").toString();
        QString q = "getaboutproject " + name + "," + goal + "," + description;
        send(q , socket);
    }
    //getmemberproject
    else if(str.split(" ").at(0) == "getmemberproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        QString q= "getmemberproject";
        while(qry.next()){
            QString username = qry.value("username").toString();
            q = q + " " + username;
        }
        send(q , socket);
    }
    //removememberproject
    else if(str.split(" ").at(0) == "removememberproject"){
        str.remove(0,in);
        qry.prepare(str);
        qry.exec();
        send("removememberproject" , socket);
    }
}









