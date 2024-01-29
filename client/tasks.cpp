#include "tasks.h"
#include "ui_tasks.h"

tasks::tasks(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tasks)
{
    ui->setupUi(this);
}

tasks::~tasks()
{
    delete ui;
}
