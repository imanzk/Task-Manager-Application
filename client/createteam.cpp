#include "createteam.h"
#include "ui_createteam.h"

createteam::createteam(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::createteam)
{
    ui->setupUi(this);
}

createteam::~createteam()
{
    delete ui;
}

void createteam::display(QString str)
{
    ui->label->setText(str);
}

void createteam::on_create_clicked()
{
    Team group;
    int size = 2;
    QLineEdit *data[size];
    data[0]=ui->name;
    data[1]=ui->department;

    for(int i = 0;i < size;i++){
        if(data[i]->text().isEmpty())
        {
            ui->label->setText("fill out the blanks");
            return;
        }
    }
    if(ui->name->text().contains(',') || ui->name->text().contains(' ')){
        ui->label->setText("',' or white space not allowed!");
        return;
    }
    if(ui->department->text().contains(',')){
        ui->label->setText("',' not allowed!");
        return;
    }
    if(ui->description->toPlainText().contains(',')){
        ui->label->setText("',' not allowed!");
        return;
    }
    group.name = data[0]->text();
    group.department = data[1]->text();
    group.description = ui->description->toPlainText();
    emit _click(group);
}

