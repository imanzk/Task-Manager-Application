#include "archived.h"
#include "ui_archived.h"

archived::archived(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::archived)
{
    ui->setupUi(this);
}

archived::~archived()
{
    delete ui;
}
