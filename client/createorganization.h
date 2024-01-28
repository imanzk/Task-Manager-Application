#ifndef CREATEORGANIZATION_H
#define CREATEORGANIZATION_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class createorganization;
}

class createorganization : public QWidget
{
    Q_OBJECT

public:
    explicit createorganization(QWidget *parent = nullptr);
    ~createorganization();
    void display(QString);
private slots:
    void on_create_clicked();
signals:
    void _click(Organization);

private:
    Ui::createorganization *ui;
};

#endif // CREATEORGANIZATION_H
