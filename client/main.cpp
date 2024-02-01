#include "mainwindow.h"
#include <QApplication>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();
}
