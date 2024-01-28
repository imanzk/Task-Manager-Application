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
    sendMessage(socket , str);
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
        send(q , socket);
    }
}









