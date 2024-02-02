#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
{
    ui->setupUi(this);
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
}

home::~home()
{
    delete ui;
}

void home::display(Organization org)
{
    list.push_back(org);
    displayButton(org);
}

void home::displayButton(Organization org)
{
    scrollLayout->setAlignment(Qt::AlignTop);
    //
    QString color;
    if(org.role=="manager")
        color = "#FF4040";
    else if(org.role == "admin")
        color = "#FF8C40";
    else if(org.role == "member")
        color = "#99D9EA";
    QPushButton *button = new QPushButton(scrollWidget);
    //
    QDrag *drag = new QDrag(button);

    connect(button , &QPushButton::clicked , this , &home::on_organclick);
    button->setStyleSheet("QPushButton{margin:5px;background:"+color+"; border-radius:'25px'; width:650px;"
                                                  " height:100px; font-size:40px; text-align:left; padding-left:30px;"
                                                  "color:white;}"
                                                  "QPushButton:hover{"
                                                  "color:"+color+";background:white;font-weight:bold;}");
    button->setText(org.name);
    button->setCursor(Qt::PointingHandCursor);
    scrollLayout->addWidget(button);
    ui->scroll->setWidget(scrollWidget);
}

void home::on_logout_clicked()
{
    emit _click(HOME::logout);
}


void home::on_tasks_clicked()
{
    emit _click(HOME::tasks);
}


void home::on_create_clicked()
{
    emit _click(HOME::create);
}


void home::on_filter_clicked()
{
    emit _click(HOME::filter);
    //
    if(filter == "all"){
        filter = "member";
        ui->filter->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else if(filter == "member"){
        filter = "admin";
        ui->filter->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else if(filter == "admin"){
        filter = "manager";
        ui->filter->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else if(filter == "manager"){
        filter = "all";
        ui->filter->setStyleSheet("background:blue;color:white;border-radius:4px;");
    }
    delete scrollLayout;
    delete scrollWidget;
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
    //
    if(filter != "all"){
        for(auto x:list)
        {
            if(filter == x.role){
                displayButton(x);
            }
        }
    }else{
        for(auto x:list)
            displayButton(x);
    }
}


void home::on_sort_clicked()
{
    emit _click(HOME::sort);
    //
    sort = !sort;
    if(sort){
        ui->sort->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else ui->sort->setStyleSheet("background:blue;color:white;border-radius:4px;");
    if(!sort) return;
    delete scrollLayout;
    delete scrollWidget;
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
    //
    std::sort(list.begin(),list.end(),[](Organization a , Organization b){return a.name<b.name;});
    for(auto &x:list){
        displayButton(x);
    }
}

void home::on_organclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(HOME::organclick , Organization(buttonSender->text()));
}

