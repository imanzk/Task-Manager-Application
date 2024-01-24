#include "loginpage.h"
#include "ui_loginpage.h"

LogInPage::LogInPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

LogInPage::~LogInPage()
{
    delete ui;
}

void LogInPage::on_CancelpushButton_clicked() //It is a slot
{
    emit _click(LogIn::key_type::cancel);
}

void LogInPage::on_OKpushButton_clicked() //It is not a slot
{
    try{
        User data = getUserData();
        emit _click(LogIn::key_type::ok , data);
    }catch(program_exception e){
        displayMessage(e.what());
    }
}
User LogInPage::getUserData()
{
    QLineEdit *data[2];
    data[0]=ui->UsernameLineEdit;
    data[1]=ui->PasswordLineEdit;

    for(int i = 0;i < 2;i++){
        if(data[i]->text().isEmpty())
        {
            program_exception e(type_exception::fill_out_blanks);
            throw e;
        }
    }
    User u;
    u.username = data[0]->text();
    u.password = data[1]->text();

    for(int i = 0;i < 2;i++){
        data[i]->text() = "";
    }
    return u;
}
void LogInPage::displayMessage(const QString stream)
{
    ui->ErrorLabel->setText(stream);
}

void LogInPage::on_recovery_clicked()
{
    emit _click(LogIn::recovery);
}

