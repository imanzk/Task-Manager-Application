#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "generics.h"

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
public:
    explicit home(QWidget *parent = nullptr);
    ~home();
    void display(Organization);

private:
    Ui::home *ui;
};

#endif // HOME_H
