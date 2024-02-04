#include "createtask.h"
#include "ui_createtask.h"

createtask::createtask(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::createtask)
{
    ui->setupUi(this);
}

createtask::~createtask()
{
    delete ui;
}

void createtask::display(QString err)
{
    ui->label->setText(err);
}

void createtask::on_create_clicked()
{
    QDateTime t = ui->date->dateTime();
    // QDateTime l = QDateTime::currentDateTime();
    // if(t>l){
    //     qDebug()<<t.toString("yyyy/MM/dd-hh:mm");
    //     qDebug()<<l.toString("yyyy/MM/dd-hh:mm");
    // }
    Task task;
    int size = 1;
    QLineEdit *data[size];
    data[0]=ui->name;

    for(int i = 0;i < size;i++){
        if(data[i]->text().isEmpty())
        {
            ui->label->setText("fill out the blank");
            return;
        }
    }
    if(ui->name->text().contains(',') || ui->name->text().contains(' ')){
        ui->label->setText("',' or white space not allowed!");
        return;
    }
    // if(ui->date->text().contains(',')){
        // ui->label->setText("',' not allowed!");
        // return;
    // }
    if(ui->description->toPlainText().contains(',')){
        ui->label->setText("',' not allowed!");
        return;
    }
    task.name = data[0]->text();
    task.date = t.toString("yyyy/MM/dd-hh:mm");
    task.description = ui->description->toPlainText();

    emit _click(task);
}

