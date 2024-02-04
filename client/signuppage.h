#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QRegularExpressionValidator>
#include "generics.h"

namespace Ui {
class signup;
}
namespace SignUp {
enum key_type{cancel , ok};
}

class SignUpPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpPage(QWidget *parent = nullptr);
    ~SignUpPage();
private:
    Ui::signup *ui;
signals:
    void _click(SignUp::key_type , User = User());
public:
    User getUserData();
    void displayMessage(const QString);
    QRegularExpressionValidator *validator;
private slots:
    void on_OKpushButton_clicked();
    void on_CancelpushButton_clicked();
    void on_checked_stateChanged(int arg1);
    void on_PasswordLineEdit_inputRejected();
};

#endif // SIGNUPPAGE_H
