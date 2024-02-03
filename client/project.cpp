#include "project.h"
#include "ui_project.h"

project::project(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::project)
{
    ui->setupUi(this);
    scrollWidgetTask = new QWidget(this);
    scrollLayoutTask = new QVBoxLayout(scrollWidgetTask);
    scrollWidgetMember = new QWidget(this);
    scrollLayoutMember = new QVBoxLayout(scrollWidgetMember);
}

project::~project()
{
    delete ui;
}

void project::init()
{
    if(curOrgan.role == "member"){
        ui->addmember->hide();
        ui->addtask->hide();
        ui->labelremove->hide();
    }
}

void project::displayMember(User u)
{
    scrollLayoutMember->setAlignment(Qt::AlignTop);
    QPushButton *button = new QPushButton(scrollWidgetMember);
    connect(button , &QPushButton::clicked , this , &project::on_memberclick);
    button->setStyleSheet("QPushButton{margin:5px;background:white; border-radius:'25px'; width:280px;"
                          " height:80px; font-size:30px; text-align:left; padding-left:30px;"
                          "color:black;}"
                          "QPushButton:hover{"
                          "color:white;background:#434445;font-weight:bold;}");
    button->setText(u.username);

    if(curOrgan.role == "member"){
        button->setDisabled(true);
    }
    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutMember->addWidget(button);
    ui->members->setWidget(scrollWidgetMember);
}

void project::displayTask(Task t)
{
    scrollLayoutTask->setAlignment(Qt::AlignTop);
    QPushButton *button = new QPushButton(scrollWidgetTask);
    connect(button , &QPushButton::clicked , this , &project::on_taskclick);
    button->setStyleSheet("QPushButton{margin:5px;background:yellow; border-radius:'25px'; width:280px;"
                          " height:80px; font-size:30px; text-align:left; padding-left:30px;"
                          "color:black;}"
                          "QPushButton:hover{"
                          "font-weight:bold;}");
    button->setText(t.name);

    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutTask->addWidget(button);
    ui->tasks->setWidget(scrollWidgetTask);
}


void project::on_back_clicked()
{
    emit _click(PROJECT::back);
}

void project::on_about_clicked()
{
    emit _click(PROJECT::about);
}


void project::on_addmember_clicked()
{
    emit _click(PROJECT::addmember);
}


void project::on_addtask_clicked()
{
    emit _click(PROJECT::addtask);
}

void project::on_memberclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Project project;
    project.user.username = buttonSender->text();
    if(curOrgan.role!="member")
        emit _click(PROJECT::memberclick , project);
}

void project::on_taskclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Project project;
    project.task.name = buttonSender->text();
    emit _click(PROJECT::taskclick , project);
}

