#include "recovery.h"
#include "ui_recovery.h"

recovery::recovery(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::recovery)
{
    ui->setupUi(this);
}

recovery::~recovery()
{
    delete ui;
}

void recovery::display(QString str)
{
    ui->label->setText(str);
}

void recovery::on_btn_clicked()
{
    QLineEdit *data[2];
    data[0]=ui->username;
    data[1]=ui->email;

    for(int i = 0;i < 2;i++){
        if(data[i]->text().isEmpty())
        {
            display("fill out the blanks");
            return;
        }
        if(data[i]->text().contains(',') || data[i]->text().contains(' ')){
            program_exception e("',' or white space not allowed!");
            throw e;
        }
    }
    User u;
    u.username = data[0]->text();
    u.email = data[1]->text();

    emit _click(u);
}

