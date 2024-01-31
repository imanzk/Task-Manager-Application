#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QWidget>

namespace Ui {
class addmember;
}

class addmember : public QWidget
{
    Q_OBJECT

public:
    explicit addmember(QWidget *parent = nullptr);
    ~addmember();

private:
    Ui::addmember *ui;
};

#endif // ADDMEMBER_H
