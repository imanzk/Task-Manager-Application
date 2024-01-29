#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class createproject;
}

class createproject : public QWidget
{
    Q_OBJECT

public:
    explicit createproject(QWidget *parent = nullptr);
    ~createproject();
    void display(QString);
private slots:
    void on_create_clicked();
signals:
    void _click(Project);
private:
    Ui::createproject *ui;
};

#endif // CREATEPROJECT_H
