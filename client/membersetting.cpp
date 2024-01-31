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
