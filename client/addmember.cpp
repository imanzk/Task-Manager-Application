#include "addmember.h"
#include "ui_addmember.h"

addmemberClass::addmemberClass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addmemberClass)
{
    ui->setupUi(this);
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
}

addmemberClass::~addmemberClass()
{
    delete ui;
}

void addmemberClass::display(QString str)
{
    if(str.isEmpty()) return;
    scrollLayout->setAlignment(Qt::AlignTop);
    QPushButton *button = new QPushButton(scrollWidget);
    connect(button , &QPushButton::clicked , this , &addmemberClass::on_userclick);
    button->setStyleSheet("background:#f7f3e4; border-radius:'2px'; width:330px;"
                          " height:80px; font-size:20px; text-align:left; padding-left:30px;"
                          "");
    button->setText(str);
    button->setCursor(Qt::PointingHandCursor);
    scrollLayout->addWidget(button);
    ui->scroll_2->setWidget(scrollWidget);
}

void addmemberClass::on_search_textEdited(const QString &arg1)
{
    if(arg1.contains(',')||arg1.contains(' ')){
        return;
    }
    delete scrollLayout;
    delete scrollWidget;
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
    emit _click(ADDMEMBER::search , User(arg1));
}

void addmemberClass::on_userclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(ADDMEMBER::userclick , User(buttonSender->text()));
}



