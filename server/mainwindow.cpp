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
    query.prepare("CREATE TABLE maha(ids integer primary key, name text)");
    query.exec();
    query.prepare("CREATE TABLE mardom(ids integer primary key, name text)");
    query.exec();
    //server
    server = new QTcpServer();

    if(server->listen(QHostAddress::Any, 8080))
    {
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
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    server->close();
    server->deleteLater();
}

void MainWindow::newConnection()
{
    while (server->hasPendingConnections())
        appendToSocketList(server->nextPendingConnection());
}

void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);
    // ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
}

void MainWindow::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="message"){
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        // emit newMessage(message);
        qDebug()<<message;
        send("hi childs");
    }
}

void MainWindow::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        // displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        connection_set.remove(*it);
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

void MainWindow::send(QString str)
{
    foreach (QTcpSocket* socket,connection_set)
    {
        sendMessage(socket , str);
        break;
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










