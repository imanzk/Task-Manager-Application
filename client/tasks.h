#ifndef TASKS_H
#define TASKS_H

#include <QWidget>

namespace Ui {
class tasks;
}

class tasks : public QWidget
{
    Q_OBJECT

public:
    explicit tasks(QWidget *parent = nullptr);
    ~tasks();

private:
    Ui::tasks *ui;
};

#endif // TASKS_H
