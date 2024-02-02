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
