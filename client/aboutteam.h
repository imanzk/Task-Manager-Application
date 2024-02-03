#ifndef ABOUTTEAM_H
#define ABOUTTEAM_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class aboutteam;
}
struct ABOUTTEAM{
    enum t{
        remove , edit
    };
};

class aboutteam : public QWidget
{
    Q_OBJECT

public:
    void display(Team);
    explicit aboutteam(QWidget *parent = nullptr);
    ~aboutteam();
signals:
    void _click(ABOUTTEAM::t , Team=Team());
private slots:
    void on_remove_clicked();

    void on_create_clicked();

private:
    Ui::aboutteam *ui;
};

#endif // ABOUTTEAM_H
