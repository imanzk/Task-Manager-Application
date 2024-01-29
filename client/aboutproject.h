#ifndef ABOUTPROJECT_H
#define ABOUTPROJECT_H

#include <QWidget>

namespace Ui {
class aboutproject;
}

class aboutproject : public QWidget
{
    Q_OBJECT

public:
    explicit aboutproject(QWidget *parent = nullptr);
    ~aboutproject();

private:
    Ui::aboutproject *ui;
};

#endif // ABOUTPROJECT_H
