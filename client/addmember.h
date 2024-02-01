#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QWidget>
#include "generics.h"
#include <QVBoxLayout>

namespace Ui {
class addmemberClass;
enum ADDMEMBER{
    search , userclick
};
}
using Ui::ADDMEMBER;

class addmemberClass : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
public:
    explicit addmemberClass(QWidget *parent = nullptr);
    ~addmemberClass();
    void display(QString);
signals:
    void _click(ADDMEMBER , User);
private slots:
    void on_search_textEdited(const QString &arg1);
    void on_userclick();
private:
    Ui::addmemberClass *ui;
};

#endif // ADDMEMBER_H
