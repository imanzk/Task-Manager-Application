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

void organization::display(Team t)
{
    if(curOrgan.role != "member"){
        ui->filterproject->hide();
        ui->filterteam->hide();
    }
    listteam.push_back(t);
    displayTeam(t);
    ui->filterteam->setText("filter");
}

void organization::display(Project p)
{
    if(curOrgan.role != "member"){
        ui->filterproject->hide();
        ui->filterteam->hide();
    }
    listproject.push_back(p);
    displayProject(p);
    ui->filterteam->setText("filter");
}

void organization::displayTeam(Team t)
{
    scrollLayoutTeam->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidgetTeam);
    connect(button , &QPushButton::clicked , this , &organization::on_teamclick);
    curTeam = t;
    button->setStyleSheet("background:#7092be; border-radius:'25px'; width:280px;"
                          " height:100px; font-size:30px; text-align:left; padding-left:30px;"
                          "color:white;");
    button->setText(t.name);
    button->setCursor(Qt::PointingHandCursor);
    scrollLayoutTeam->addWidget(button);
    ui->teams->setWidget(scrollWidgetTeam);
}

void organization::displayProject(Project p)
{
    scrollLayoutProject->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidgetProject);
    connect(button , &QPushButton::clicked , this , &organization::on_projectclick);
    button->setStyleSheet("background:#818181; border-radius:'25px'; width:280px;"
                          " height:100px; font-size:30px; text-align:left; padding-left:30px;"
                          "color:white;");
    button->setText(p.name);
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
    //
    if(filterteam == "all"){
        filterteam = "member";
    }else if(filterteam == "member"||filterteam=="director"){
        filterteam = "all";
    }
    ui->filterteam->setText("filter:"+filterteam);
    //
    delete scrollLayoutTeam;
    delete scrollWidgetTeam;
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    //
    if(filterteam != "all"){
        for(auto x:listteam)
        {
            if(filterteam == x.role){
                displayTeam(x);
            }
        }
    }else{
        for(auto x:listteam)
            displayTeam(x);
    }
}


void organization::on_filterproject_clicked()
{
    emit _click(ORGAN::filterproject);
    //
    if(filterproject == "all"){
        filterproject = "member";
    }else if(filterproject == "member"||filterproject =="director"){
        filterproject = "all";
    }
    ui->filterproject->setText("filter:"+filterproject);
    //
    delete scrollLayoutProject;
    delete scrollWidgetProject;
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
    //
    if(filterproject != "all"){
        for(auto x:listproject)
        {
            if(filterproject == x.role){
                displayProject(x);
            }
        }
    }else{
        for(auto x:listproject)
            displayProject(x);
    }
}


void organization::on_sortproject_clicked()
{
    emit _click(ORGAN::sortproject);
    //
    delete scrollLayoutProject;
    delete scrollWidgetProject;
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
    //
    std::sort(listproject.begin(),listproject.end(),[](Project a , Project b){return a.name<b.name;});
    for(auto &x:listproject){
        displayProject(x);
    }
    ui->filterproject->setText("filter");
}

void organization::on_sortteam_clicked()
{
    emit _click(ORGAN::sortteam);
    //
    delete scrollLayoutTeam;
    delete scrollWidgetTeam;
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    //
    std::sort(listteam.begin(),listteam.end(),[](Team a , Team b){return a.name<b.name;});
    for(auto &x:listteam){
        displayTeam(x);
    }
    ui->filterteam->setText("filter");
}

void organization::on_teamclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(ORGAN::teamclick , Group(buttonSender->text(),"team"));
}

void organization::on_projectclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(ORGAN::teamclick , Group(buttonSender->text(),"project"));
}

