#include "addcomment.h"
#include "ui_addcomment.h"

addcomment::addcomment(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addcomment)
{
    ui->setupUi(this);
}

addcomment::~addcomment()
{
    delete ui;
}

void addcomment::on_edit_clicked()
{
    if(ui->comment->toPlainText().contains(',')){
        ui->error->setText("',' not allowed!");
        return;
    }
    if(ui->comment->toPlainText().isEmpty()){
        ui->error->setText("fill out the blank!");
    }else{
        QString comment = ui->comment->toPlainText();
        emit _click(comment);
    }
}

