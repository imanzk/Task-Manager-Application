#include "entrancepage.h"
#include "ui_entrancepage.h"

EntrancePage::EntrancePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
}

EntrancePage::~EntrancePage() {
    delete ui;
}

void EntrancePage::on_Login_pushButton_clicked(){
    emit _click(Entrance::key_type::login);
}


void EntrancePage::on_Signup_pushButton_clicked(){
    emit _click(Entrance::key_type::signup);
}
