#ifndef MEMBERSETTING_H
#define MEMBERSETTING_H

#include <QWidget>

namespace Ui {
class membersetting;
}

class membersetting : public QWidget
{
    Q_OBJECT

public:
    explicit membersetting(QWidget *parent = nullptr);
    ~membersetting();

private:
    Ui::membersetting *ui;
};

#endif // MEMBERSETTING_H
