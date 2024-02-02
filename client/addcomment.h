#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include <QWidget>

namespace Ui {
class addcomment;
}

class addcomment : public QWidget
{
    Q_OBJECT

public:
    explicit addcomment(QWidget *parent = nullptr);
    ~addcomment();

private:
    Ui::addcomment *ui;
};

#endif // ADDCOMMENT_H
