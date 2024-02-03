#ifndef ABOUTPROJECT_H
#define ABOUTPROJECT_H

#include <QWidget>
#include "generics.h"

namespace Ui {
class aboutproject;
}
struct ABOUTPROJECT{
    enum t{
        remove , edit
    };
};

class aboutproject : public QWidget
{
    Q_OBJECT

public:
    explicit aboutproject(QWidget *parent = nullptr);
    ~aboutproject();
    void display(Project);
private slots:
    void on_create_clicked();

    void on_remove_clicked();
signals:
    void _click(ABOUTPROJECT::t , Project);
private:
    Ui::aboutproject *ui;
};

#endif // ABOUTPROJECT_H
