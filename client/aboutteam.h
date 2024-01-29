#ifndef ABOUTTEAM_H
#define ABOUTTEAM_H

#include <QWidget>

namespace Ui {
class aboutteam;
}

class aboutteam : public QWidget
{
    Q_OBJECT

public:
    explicit aboutteam(QWidget *parent = nullptr);
    ~aboutteam();

private:
    Ui::aboutteam *ui;
};

#endif // ABOUTTEAM_H
