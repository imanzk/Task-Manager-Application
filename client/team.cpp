#include "team.h"
#include "ui_team.h"

team::team(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::team)
{
    ui->setupUi(this);
    scrollWidgetTask = new QWidget(this);
    scrollLayoutTask = new QVBoxLayout(scrollWidgetTask);
    scrollWidgetMember = new QWidget(this);
    scrollLayoutMember = new QVBoxLayout(scrollWidgetMember);
}

team::~team()
{
    delete ui;
}

void team::init()
{
    if(curTeam.role == "member"||curTeam.role=="director"){
        ui->addmember->hide();
        ui->addtask->hide();
    }
}

void team::on_back_clicked()
{
    emit _click(TEAM::back);
}


void team::on_about_clicked()
{
    emit _click(TEAM::about);
}


void team::on_addmember_clicked()
{
    emit _click(TEAM::addmember);
}


void team::on_addtask_clicked()
{
    emit _click(TEAM::addtask);
}

void team::displayMember(User u)
{
    scrollLayoutMember->setAlignment(Qt::AlignTop);
    QPushButton *button = new QPushButton(scrollWidgetMember);
    connect(button , &QPushButton::clicked , this , &team::on_memberclick);
    button->setStyleSheet("QPushButton{margin:5px;background:white; border-radius:'25px'; width:280px;"
                                                                         " height:80px; font-size:30px; text-align:left; padding-left:30px;"
                                                                         "color:black;}"
                                                                         "QPushButton:hover{"
                                                                         "color:white;background:#434445;font-weight:bold;}");
    if(u.role == "member"){
        button->setText(u.username);
    }
    else{
        button->setText(u.username+" ("+u.role+")");
    }
    //
    if(curTeam.role == "member"){
        button->setDisabled(true);
    }
    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutMember->addWidget(button);
    ui->members->setWidget(scrollWidgetMember);
}

void team::displayTask(Task t)
{
    scrollLayoutTask->setAlignment(Qt::AlignTop);
    QPushButton *button = new QPushButton(scrollWidgetTask);
    connect(button , &QPushButton::clicked , this , &team::on_taskclick);
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

void team::on_memberclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Team team;
    QStringList l = buttonSender->text().split(" ");
    if(l.size()==1){
        team.username = l[0];
        team.role = "member";
    }else if(l.size()==2){
        l[1].remove("(");
        l[1].remove(")");
        team.role = l[1];
        team.username = l[0];
    }
    if(curOrg.role!="member")
        emit _click(TEAM::memberclick , team);
    // else{
    //     emit _click(TEAM::memberclicktask , team);
    // }
}

void team::on_taskclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Team team;
    team.task.name = buttonSender->text();
    emit _click(TEAM::taskclick , team);
}

