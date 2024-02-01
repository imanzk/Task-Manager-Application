#include "membersetting.h"
#include "ui_membersetting.h"

membersetting::membersetting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::membersetting)
{
    ui->setupUi(this);
}

membersetting::~membersetting()
{
    delete ui;
}

void membersetting::init(User u)
{
    user = u;
    ui->upgrade->setText(u.role=="admin"?"disgrade to member":"upgrade to admin");
    ui->label->setText(u.username);
}

void membersetting::on_upgrade_clicked()
{
    if(user.role=="admin")
        emit _click(MEMBERSETTING::disgrade,user);
    else if(user.role=="member")
        emit _click(MEMBERSETTING::upgrade,user);
}


void membersetting::on_remove_clicked()
{
    emit _click(MEMBERSETTING::clear,user);
}

