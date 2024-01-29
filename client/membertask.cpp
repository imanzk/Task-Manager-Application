#include "membertask.h"
#include "ui_membertask.h"

membertask::membertask(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::membertask)
{
    ui->setupUi(this);
}

membertask::~membertask()
{
    delete ui;
}
