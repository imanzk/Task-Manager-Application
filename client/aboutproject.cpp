#include "aboutproject.h"
#include "ui_aboutproject.h"

aboutproject::aboutproject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::aboutproject)
{
    ui->setupUi(this);
}

aboutproject::~aboutproject()
{
    delete ui;
}
