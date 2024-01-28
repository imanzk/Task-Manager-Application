#include "organization.h"
#include "ui_organization.h"

organization::organization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::organization)
{
    ui->setupUi(this);
}

organization::~organization()
{
    delete ui;
}



