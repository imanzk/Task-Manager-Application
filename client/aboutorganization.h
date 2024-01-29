#ifndef ABOUTORGANIZATION_H
#define ABOUTORGANIZATION_H

#include <QWidget>

namespace Ui {
class aboutorganization;
}

class aboutorganization : public QWidget
{
    Q_OBJECT

public:
    explicit aboutorganization(QWidget *parent = nullptr);
    ~aboutorganization();

private:
    Ui::aboutorganization *ui;
};

#endif // ABOUTORGANIZATION_H
