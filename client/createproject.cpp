#include "createproject.h"
#include "ui_createproject.h"

createproject::createproject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::createproject)
{
    ui->setupUi(this);
}

createproject::~createproject()
{
    delete ui;
}
void createproject::display(QString str)
{
    ui->label->setText(str);
}

void createproject::on_create_clicked()
{
    Project group;
    int size = 2;
    QLineEdit *data[size];
    data[0]=ui->name;
    data[1]=ui->goal;

    for(int i = 0;i < size;i++){
        if(data[i]->text().isEmpty())
        {
            ui->label->setText("fill out the blanks");
            return;
        }
    }
    group.name = data[0]->text();
    group.goal = data[1]->text();
    group.description = ui->description->toPlainText();
    emit _click(group);
}

