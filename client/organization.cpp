#include "organization.h"
#include "ui_organization.h"

organization::organization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::organization)
{
    ui->setupUi(this);
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
}

organization::~organization()
{
    delete ui;
}

void organization::displayTeam(Group g)
{
    QPushButton *button = new QPushButton(scrollWidgetTeam);
    connect(button , &QPushButton::clicked , [&](){
        emit _click(ORGAN::teamclick , g);
    });
    button->setStyleSheet("background:#7092be; border-radius:'25px'; width:450px;"
                            " height:130px; font-size:30px; text-align:left; padding-left:30px;"
                            "");
    button->setText(g.name);
    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutTeam->addWidget(button);
    ui->teams->setWidget(scrollWidgetTeam);
}

void organization::displayProject(Group g)
{
    QPushButton *button = new QPushButton(scrollWidgetProject);
    connect(button , &QPushButton::clicked , [&](){
        emit _click(ORGAN::projectclick , g);
    });
    button->setStyleSheet("background:#7f7f7f; border-radius:'25px'; width:450px;"
                          " height:130px; font-size:30px; text-align:left; padding-left:30px;"
                          "");
    button->setText(g.name);
    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutProject->addWidget(button);
    ui->projects->setWidget(scrollWidgetProject);
}


void organization::on_home_clicked()
{
    emit _click(ORGAN::home);
}


void organization::on_about_clicked()
{
    emit _click(ORGAN::about);
}


void organization::on_createTeam_clicked()
{
    emit _click(ORGAN::createTeam);
}


void organization::on_createProject_clicked()
{
    emit _click(ORGAN::creatProject);
}


void organization::on_filterteam_clicked()
{
    emit _click(ORGAN::filterteam);
}


void organization::on_sortteam_clicked()
{
    emit _click(ORGAN::sortteam);
}


void organization::on_filterproject_clicked()
{
    emit _click(ORGAN::filterproject);
}


void organization::on_sortproject_clicked()
{
    emit _click(ORGAN::sortproject);
}

