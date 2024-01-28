#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QWidget>

namespace Ui {
class organization;
}

class organization : public QWidget
{
    Q_OBJECT

public:
    explicit organization(QWidget *parent = nullptr);
    ~organization();

private slots:

private:
    Ui::organization *ui;
};

#endif // ORGANIZATION_H
