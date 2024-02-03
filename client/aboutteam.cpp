#include "aboutteam.h"
#include "ui_aboutteam.h"

void aboutteam::display(Team team)
{
    ui->name->setText(team.name);
    ui->name->setDisabled(true);
    ui->department->setText(team.department);
    ui->description->setText(team.description);
    if(team.role == "member"){
        ui->create->hide();
        ui->remove->hide();
        ui->department->setDisabled(true);
        ui->description->setDisabled(true);
    }
}

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

void aboutteam::on_remove_clicked()
{
    Team team;
    team.name = ui->name->text();
    emit _click(ABOUTTEAM::remove , team);
}


void aboutteam::on_create_clicked()
{
    Team team;

    if(ui->department->text().isEmpty())
    {
        ui->label->setText("fill out the blank");
        return;
    }

    team.name = ui->name->text();
    team.department = ui->department->text();
    team.description = ui->description->toPlainText();

    emit _click(ABOUTTEAM::edit , team);
}

