#include "aboutorganization.h"
#include "ui_aboutorganization.h"

aboutorganization::aboutorganization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::aboutorganization)
{
    ui->setupUi(this);
}

aboutorganization::~aboutorganization()
{
    delete ui;
}
