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

void aboutproject::display(Project project)
{
    // qDebug()<<project.name << project.goal << project.description << project.role;
    ui->name->setText(project.name);
    ui->name->setDisabled(true);
    ui->status->setText(project.goal);
    ui->description->setText(project.description);
    if(project.role == "member"){
        ui->create->hide();
        ui->remove->hide();
        ui->status->setDisabled(true);
        ui->description->setDisabled(true);
    }
}

void aboutproject::on_remove_clicked()
{
    Project project;
    project.name = ui->name->text();
    emit _click(ABOUTPROJECT::remove , project);
}


void aboutproject::on_create_clicked()
{
    Project project;

    if(ui->status->text().isEmpty())
    {
        ui->label->setText("fill out the blank");
        return;
    }
    if(ui->name->text().contains(',') || ui->name->text().contains(' ')){
        ui->label->setText("',' or white space not allowed!");
        return;
    }
    if(ui->status->text().contains(',')){
        ui->label->setText("',' not allowed!");
        return;
    }
    if(ui->description->toPlainText().contains(',')){
        ui->label->setText("',' not allowed!");
        return;
    }
    project.name = ui->name->text();
    project.goal = ui->status->text();
    project.description = ui->description->toPlainText();

    emit _click(ABOUTPROJECT::edit , project);
}

