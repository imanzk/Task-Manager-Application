#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void sendMessage(QTcpSocket* socket , QString);

public:
    void send(QString); // to use
public slots:
    void get(QString);

signals:
    void newMessage(QString); // to use


private:

    QTcpServer* server;
    QSet<QTcpSocket*> connection_set;

};
#endif // MAINWINDOW_H
