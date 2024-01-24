#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
{
    ui->setupUi(this);
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);

    // for (int i = 0; i < 2; ++i) {
    //     QPushButton *button = new QPushButton(scrollWidget);
    //     button->setStyleSheet("background:blue; border-radius:'25px'; width:750px; height:130px; font-size:30px; text-align:left; padding-left:30px;");
    //     button->setText("LG                                                                                   10 member");
    //     scrollLayout->addWidget(button);
    // }

    ui->scroll->setWidget(scrollWidget);

}

home::~home()
{
    delete ui;
}

void home::display(Organization org)
{
    QString color;
    if(org.role=="manager")
        color = "#FF4040";
    else if(org.role == "admin")
        color = "#FF8C40";
    else if(org.role == "member")
        color = "#99D9EA";
    QPushButton *button = new QPushButton(scrollWidget);
    button->setStyleSheet("background:"+color+"; border-radius:'25px'; width:750px; height:130px; font-size:30px; text-align:left; padding-left:30px;");
    // button->setText("LG                                                                                   10 member");
    button->setText(org.name);
    scrollLayout->addWidget(button);
    ui->scroll->setWidget(scrollWidget);
}
