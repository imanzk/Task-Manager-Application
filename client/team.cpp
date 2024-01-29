#include "team.h"
#include "ui_team.h"

team::team(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::team)
{
    ui->setupUi(this);
}

team::~team()
{
    delete ui;
}
