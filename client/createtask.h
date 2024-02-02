#ifndef CREATETASK_H
#define CREATETASK_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class createtask;
}

class createtask : public QWidget
{
    Q_OBJECT

public:
    explicit createtask(QWidget *parent = nullptr);
    ~createtask();
    void display(QString err);
private slots:
    void on_create_clicked();
signals:
    void _click(Task);
private:
    Ui::createtask *ui;
};

#endif // CREATETASK_H
