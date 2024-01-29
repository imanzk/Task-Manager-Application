#ifndef TEAM_H
#define TEAM_H

#include <QWidget>

namespace Ui {
class team;
}

class team : public QWidget
{
    Q_OBJECT

public:
    explicit team(QWidget *parent = nullptr);
    ~team();

private:
    Ui::team *ui;
};

#endif // TEAM_H
