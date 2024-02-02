#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class task;
}

class task : public QWidget
{
    Q_OBJECT

public:
    explicit task(QWidget *parent = nullptr);
    ~task();

private:
    Ui::task *ui;
};

#endif // TASK_H
