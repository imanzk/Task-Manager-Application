#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "generics.h"

namespace LogIn{
enum key_type{cancel , ok , recovery};
}
namespace Ui {
class login;
}

class LogInPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

private:
    Ui::login *ui;
signals:
    void _click(LogIn::key_type ,User = User());
public:
    User getUserData();
    void displayMessage(const QString);

private slots:
    void on_OKpushButton_clicked();
    void on_CancelpushButton_clicked();

    void on_recovery_clicked();
    void on_checked_stateChanged(int arg1);
};

#endif // LOGINPAGE_H
