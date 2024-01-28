#include "createorganization.h"
#include "ui_createorganization.h"

createorganization::createorganization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::createorganization)
{
    ui->setupUi(this);
}

createorganization::~createorganization()
{
    delete ui;
}

void createorganization::display(QString str)
{
    ui->label->setText(str);
}

void createorganization::on_create_clicked()
{
    Organization org;
    int size = 3;
    QLineEdit *data[size];
    data[0]=ui->name;
    data[1]=ui->type;
    data[2]=ui->description;

    for(int i = 0;i < size;i++){
        if(data[i]->text().isEmpty())
        {
            ui->label->setText("fill out the blanks");
            return;
        }
    }
    org.name = data[0]->text();
    org.type = data[1]->text();
    org.description = data[2]->text();

    emit _click(org);
}

