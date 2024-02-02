#include "membersettingteam.h"
#include "ui_membersettingteam.h"

membersettingteam::membersettingteam(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::membersettingteam)
{
    ui->setupUi(this);
}

membersettingteam::~membersettingteam()
{
    delete ui;
}

void membersettingteam::init(User u){
    user = u;
    ui->upgrade->setText(u.role=="director"?"disgrade to member":"upgrade to director");
    ui->label->setText(u.username);
}

void membersettingteam::on_upgrade_clicked()
{
    if(user.role=="director")
        emit _click(MEMBERSETTINGTEAM::disgrade,user);
    else if(user.role=="member")
        emit _click(MEMBERSETTINGTEAM::upgrade,user);
}


void membersettingteam::on_remove_clicked()
{
    emit _click(MEMBERSETTINGTEAM::clear,user);
}

