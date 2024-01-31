#include "addmember.h"
#include "ui_addmember.h"

addmember::addmember(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addmember)
{
    ui->setupUi(this);
}

addmember::~addmember()
{
    delete ui;
}
