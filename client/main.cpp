#include "mainwindow.h"
#include <QApplication>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
using namespace admin;
void loop(MainWindow *w , PLACE *place){
    while(1){
        QThread::msleep(2000);
        if(*place == admin::home)
            w->createHome();
        else if(*place == admin::organization)
            w->createOrgan();
        else if(*place == admin::organization)
            w->createOrgan();
        else if(*place == admin::about_organization)
            w->createAboutorganization();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    repeat l;
    l.start();
    // QFuture<void>future = QtConcurrent::run(loop,&w , &w.place);
    return a.exec();
}
