#ifndef CREATETEAM_H
#define CREATETEAM_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class createteam;
}

class createteam : public QWidget
{
    Q_OBJECT

public:
    explicit createteam(QWidget *parent = nullptr);
    ~createteam();
    void display(QString);
private slots:
    void on_create_clicked();
signals:
    void _click(Team);

private:
    Ui::createteam *ui;
};

#endif // CREATETEAM_H
