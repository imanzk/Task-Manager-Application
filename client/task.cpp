#include "task.h"
#include "ui_task.h"

void task::init()
{//we have curTask;
    ui->name->setDisabled(true);
    ui->name->setText(curTask.name);
    ui->date->setDateTime(QDateTime::fromString(curTask.date,"yyyy/MM/dd-hh:mm"));
    ui->description->setText(curTask.description);
    ui->description->setDisabled(true);
    ui->description->setDisabled(false);
    ui->edit->hide();
    if(curOrgan.role == "member" && curTeam.role == "member"){
        ui->date->setDisabled(true);
        ui->description->setDisabled(true);
        ui->remove->hide();
        ui->addmember->hide();
        ui->labelremove->hide();
        ui->unassign->hide();
    }
}

task::task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::task)
{
    ui->setupUi(this);
    scrollWidgetMember = new QWidget(this);
    scrollLayoutMember = new QVBoxLayout(scrollWidgetMember);
    scrollWidgetComment = new QWidget(this);
    scrollLayoutComment = new QVBoxLayout(scrollWidgetComment);
}

task::~task()
{
    delete ui;
}

void task::displayUser(User user)
{
    scrollLayoutMember->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidgetMember);
    connect(button , &QPushButton::clicked , this , &task::memberclick);
    button->setStyleSheet("background:#ffc800; border-radius:'2px'; width:200px;"
                          " height:50px; font-size:20px; text-align:left; padding-left:30px;"
                          "color:black;");
    if(curOrgan.role == "member" && curTeam.role == "member"){
        button->setDisabled(true);
    }
    button->setText(user.username);
    scrollLayoutMember->addWidget(button);
    ui->users->setWidget(scrollWidgetMember);
}

void task::displayComment(QString comment)
{
    scrollLayoutComment->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidgetComment);
    connect(button , &QPushButton::clicked , this , &task::commentclick);
    button->setStyleSheet("background:white; border-radius:'2px';"
                          "font-size:15px; text-align:left; padding:2px;"
                          "color:black;");
    if(curOrgan.role == "member" && curTeam.role == "member"){
        button->setDisabled(true);
    }
    button->setText(comment);
    scrollLayoutComment->addWidget(button);
    ui->comments->setWidget(scrollWidgetComment);
}

void task::memberclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Task task;
    task.user.username = buttonSender->text();
    task.name = curTask.name;
    emit _click(TASKPAGE::memberclick , task);
}

void task::commentclick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Task task;
    task.name = curTask.name;
    task.comment = buttonSender->text();
    emit _click(TASKPAGE::commentclick , task);
}

void task::on_remove_clicked()
{
    Task task;
    task.name = ui->name->text();
    emit _click(TASKPAGE::remove , task);
}


void task::on_edit_clicked()
{
    Task task;

    if(ui->date->text().isEmpty())
    {
        ui->error->setText("fill out the blanks");
        return;
    }
    if(ui->name->text().contains(',') || ui->name->text().contains(' ')){
        ui->error->setText("',' or white space not allowed!");
        return;
    }
    // if(ui->type->text().contains(',')){
        // ui->error->setText("',' not allowed!");
        // return;
    // }
    if(ui->description->toPlainText().contains(',')){
        ui->error->setText("',' not allowed!");
        return;
    }

    task.name = ui->name->text();
    task.date = ui->date->dateTime().toString("yyyy/MM/dd-hh:mm");
    task.description = ui->description->toPlainText();

    emit _click(TASKPAGE::edit , task);
    ui->edit->hide();
}


void task::on_addmember_clicked()
{
    emit _click(TASKPAGE::addmember);
}


void task::on_addcomment_clicked()
{
    emit _click(TASKPAGE::addcomment);
}


void task::on_date_dateTimeChanged(const QDateTime &dateTime)
{
    ui->edit->show();
}



void task::on_back_clicked()
{
    emit _click(TASKPAGE::back);
}


void task::on_description_textChanged()
{
    ui->edit->show();
}

