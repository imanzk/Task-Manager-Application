#include "signuppage.h"
#include "ui_signuppage.h"

SignUpPage::SignUpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

SignUpPage::~SignUpPage()
{
    delete ui;
}

void SignUpPage::on_CancelpushButton_clicked()
{
    emit _click(SignUp::key_type::cancel);
}

void SignUpPage::on_OKpushButton_clicked()
{
    try{
        User data = getUserData();
        emit _click(SignUp::key_type::ok , data);
    }catch(program_exception e){
        displayMessage(e.what());
    }
}
User SignUpPage::getUserData()
{
    int size = 4;
    QLineEdit *data[size];
    data[0]=ui->UsernameLineEdit;
    data[1]=ui->PasswordLineEdit;
    data[2]=ui->FullNameLineEdit;
    data[3]=ui->EmailLineEdit;
    for(int i = 0;i < size;i++){
        if(data[i]->text().isEmpty())
        {
            program_exception e(type_exception::fill_out_blanks);
            throw e;
        }
    }

    User u;
    u.username = data[0]->text();
    u.password = data[1]->text();
    u.name = data[2]->text();
    u.email = data[3]->text();

    for(int i = 0;i < size;i++){
        data[i]->text() = "";
    }
    return u;
}

void SignUpPage::displayMessage(const QString stream)
{
    ui->ErrorLabel->setText(stream);
}


