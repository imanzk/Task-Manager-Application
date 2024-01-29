#include "aboutteam.h"
#include "ui_aboutteam.h"

aboutteam::aboutteam(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::aboutteam)
{
    ui->setupUi(this);
}

aboutteam::~aboutteam()
{
    delete ui;
}
