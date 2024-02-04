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
#include <QThread>

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh();
private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void sendMessage(QTcpSocket* socket , QString);

public:
    void send(QString str, QTcpSocket* = nullptr); // to use
public slots:
    void get(QString ,QTcpSocket*);

signals:
    void newMessage(QString ,QTcpSocket*); // to use


private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QVector<QTcpSocket*> connections;

};
#endif // MAINWINDOW_H
