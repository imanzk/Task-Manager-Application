#include "organization.h"
#include "ui_organization.h"


void organization::init()
{
    if(curOrgan.role == "member"){
        ui->createProject->hide();
        ui->createTeam->hide();
    }
}

organization::organization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::organization)
{
    ui->setupUi(this);
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
    //
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
    button->setStyleSheet("QPushButton{margin:5px;background:#7092be; border-radius:'25px'; width:300px;"
                          " height:80px; font-size:40px; text-align:left; padding-left:30px;"
                          "color:white;}"
                          "QPushButton:hover{"
                          "color:#7092be;background:white;font-weight:bold;}");
    button->setText(t.name);
    button->setCursor(Qt::PointingHandCursor);
    if(!t.available && curOrgan.role=="member"){
        button->setDisabled(true);
        button->setCursor(Qt::ArrowCursor);
    }
    scrollLayoutTeam->addWidget(button);
    ui->teams->setWidget(scrollWidgetTeam);
}

void organization::displayProject(Project p)
{
    scrollLayoutProject->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidgetProject);
    connect(button , &QPushButton::clicked , this , &organization::on_projectclick);
    button->setStyleSheet("QPushButton{margin:5px;background:#818181; border-radius:'25px'; width:300px;"
                          " height:80px; font-size:40px; text-align:left; padding-left:30px;"
                          "color:white;}"
                          "QPushButton:hover{"
                          "color:#818181;background:white;font-weight:bold;}");
    button->setText(p.name);
    button->setCursor(Qt::PointingHandCursor);
    if(!p.available && curOrgan.role=="member"){
        button->setDisabled(true);
        button->setCursor(Qt::ArrowCursor);
    }
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
    // emit _click(ORGAN::filterteam);
    //
    if(filterteam == "all"){
        filterteam = "member";
        ui->filterteam->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else if(filterteam == "member"||filterteam=="director"){
        filterteam = "all";
        ui->filterteam->setStyleSheet("background:blue;color:white;border-radius:4px;");
    }
    //
    delete scrollLayoutTeam;
    delete scrollWidgetTeam;
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    //
    if(filterteam != "all"){
        for(auto x:listteam)
        {
            if(x.available){
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
    // emit _click(ORGAN::filterproject);
    //
    if(filterproject == "all"){
        filterproject = "member";
        ui->filterproject->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    }else if(filterproject == "member"||filterproject =="director"){
        filterproject = "all";
        ui->filterproject->setStyleSheet("background:blue;color:white;border-radius:4px;");
    }
    delete scrollLayoutProject;
    delete scrollWidgetProject;
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
    //
    if(filterproject != "all"){
        for(auto x:listproject)
        {
            if(x.available){
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
    // emit _click(ORGAN::sortproject);
    //
    sortproject = !sortproject;
    if(sortproject)
        ui->sortproject->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    else ui->sortproject->setStyleSheet("background:blue;color:white;border-radius:4px;");
    if(!sortproject) return;
    delete scrollLayoutProject;
    delete scrollWidgetProject;
    scrollWidgetProject = new QWidget(this);
    scrollLayoutProject = new QVBoxLayout(scrollWidgetProject);
    //
    std::sort(listproject.begin(),listproject.end(),[](Project a , Project b){return a.name<b.name;});
    for(auto &x:listproject){
        displayProject(x);
    }
}

void organization::on_sortteam_clicked()
{
    // emit _click(ORGAN::sortteam);
    //
    sortteam = !sortteam;
    if(sortteam)
        ui->sortteam->setStyleSheet("background:#e4f1f7;color:black;border-radius:4px;");
    else ui->sortteam->setStyleSheet("background:blue;color:white;border-radius:4px;");
    if(!sortteam) return;
    delete scrollLayoutTeam;
    delete scrollWidgetTeam;
    scrollWidgetTeam = new QWidget(this);
    scrollLayoutTeam = new QVBoxLayout(scrollWidgetTeam);
    //
    std::sort(listteam.begin(),listteam.end(),[](Team a , Team b){return a.name<b.name;});
    for(auto &x:listteam){
        displayTeam(x);
    }
}

void organization::on_teamclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(ORGAN::teamclick , Group(buttonSender->text(),"team"));
}

void organization::on_projectclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    emit _click(ORGAN::projectclick , Group(buttonSender->text(),"project"));
}

