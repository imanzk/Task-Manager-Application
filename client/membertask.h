#ifndef MEMBERTASK_H
#define MEMBERTASK_H

#include <QWidget>

namespace Ui {
class membertask;
}

class membertask : public QWidget
{
    Q_OBJECT

public:
    explicit membertask(QWidget *parent = nullptr);
    ~membertask();

private:
    Ui::membertask *ui;
};

#endif // MEMBERTASK_H
