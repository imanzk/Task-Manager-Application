#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    connections.insert("NULL",socket);
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
    QString key = connections.key(socket);
    qDebug() << "disconnected " << key;
    connections.remove(key);
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
    QThread::msleep(1);
    qDebug() << "get:" << str;
    //signup
    QSqlQuery qry;
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
        str.remove(0,9);
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
        str.remove(0,4);
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
        str.remove(0 , 7);
        connections.insert(str,socket);
        qDebug() << "connected as " << str;
    }
    //home
    else if(str.split(" ").at(0) == "home"){
        str.remove(0,5);
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
        str.remove(0,5);
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
    //getteam
    else if(str.split(" ").at(0) == "getteam"){
        str.remove(0,8);
        qry.prepare(str);
        qry.exec();
        //
        QString q = "getteam";
        QString team;
        while(qry.next()){
            team = qry.value("team").toString();
            q = q + " " + team;
        }
        send(q,socket);
    }
    //getproject
    else if(str.split(" ").at(0) == "getproject"){
        str.remove(0, 11);
        qry.prepare(str);
        qry.exec();
        //
        QString q = "getproject";
        QString project;
        while(qry.next()){
            project = qry.value("project").toString();
            q = q + " " + project;
        }
        send(q,socket);
    }
    //getmemberorg
    else if(str.split(" ").at(0) == "getmemberorg"){
        str.remove(0,13);
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
        str.remove(0,10);
        qry.prepare(str);
        qry.exec();
        //
        send("editorgan",socket);
    }
    //getrole
    else if(str.split(" ").at(0) == "getrole"){
        str.remove(0,8);
        qry.prepare(str);
        qry.exec();
        qry.next();
        send("getrole "+qry.value("role").toString(),socket);
    }
    //curorgan
    else if(str.split(" ").at(0) == "curorgan"){
        str.remove(0,9);
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
        str.remove(0,12);
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
        send("removeorgan",socket);
    }
}









