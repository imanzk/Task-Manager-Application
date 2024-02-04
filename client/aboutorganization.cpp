#include "aboutorganization.h"
#include "ui_aboutorganization.h"

aboutorganization::aboutorganization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::aboutorganization)
{
    ui->setupUi(this);
    scrollWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidget);
    //
    ui->remove->hide();
    ui->edit->hide();
    ui->name->setDisabled(true);
    ui->type->setDisabled(true);
    ui->description->setDisabled(true);
    ui->addmember->hide();
    ui->edit->hide();
}

aboutorganization::~aboutorganization()
{
    delete ui;
}

void aboutorganization::displayOrgan(Organization org)
{
    curOrgan = org;
    if(curOrgan.role == "manager"){
        // ui->name->setEnabled(true);
        ui->type->setEnabled(true);
        ui->description->setEnabled(true);
        ui->addmember->show();
        ui->remove->show();
    }
    ui->name->setText(org.name);
    ui->type->setText(org.type);
    ui->description->setText(org.description);
    ui->edit->hide();
}

void aboutorganization::display(User u)
{
    list.push_back(u);
    displayMember(u);
}

void aboutorganization::displayMember(User u)
{
    scrollLayout->setAlignment(Qt::AlignTop);
    //
    QPushButton *button = new QPushButton(scrollWidget);
    connect(button , &QPushButton::clicked , this , &aboutorganization::on_memberclicked);
    button->setStyleSheet("background:#ffc800; border-radius:'2px'; width:300px;"
                          " height:50px; font-size:20px; text-align:left; padding-left:30px;"
                          "color:black;");

    if(u.role == "admin" || u.role == "manager")
        button->setText(u.role+": "+u.username);
    else
        button->setText(u.username);
    if(curOrgan.role == "manager"){
        if(u.role == "manager"){
            button->setCursor(Qt::ArrowCursor);
            button->setDisabled(true);
        }
        else{
            button->setCursor(Qt::PointingHandCursor);
            button->setDisabled(false);
        }
    }else if(curOrgan.role == "admin" || curOrgan.role == "member"){
        button->setDisabled(true);
    }
    scrollLayout->addWidget(button);
    ui->scroll->setWidget(scrollWidget);
}

void aboutorganization::on_addmember_clicked()
{
    emit _click(ABOUTORGAN::addmember);
}


void aboutorganization::on_back_clicked()
{
    emit _click(ABOUTORGAN::back);
}

void aboutorganization::on_memberclicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Organization org;
    QStringList l = buttonSender->text().split(" ");
    if(l.size()==1){
        org.username = l[0];
        org.role = "member";
    }else if(l.size()==2){
        l[0].remove(":");
        org.role = l[0];
        org.username = l[1];
    }
    emit _click(ABOUTORGAN::memberclick , org);
}


void aboutorganization::on_edit_clicked()
{
    Organization org;

    if(ui->type->text().isEmpty())
    {
        ui->error->setText("fill out the blanks");
        return;
    }
    //
    if(ui->name->text().contains(',') || ui->name->text().contains(' ')){
        ui->error->setText("',' or white space not allowed!");
        return;
    }
    if(ui->type->text().contains(',')){
        ui->error->setText("',' not allowed!");
        return;
    }
    if(ui->description->toPlainText().contains(',')){
        ui->error->setText("',' not allowed!");
        return;
    }
    org.name = ui->name->text();
    org.type = ui->type->text();
    org.description = ui->description->toPlainText();

    emit _click(ABOUTORGAN::edit , org);
    ui->edit->hide();
}


void aboutorganization::on_type_textEdited(const QString &arg1)
{
    if(curOrgan.role == "manager"){
        ui->edit->show();
    }
}


void aboutorganization::on_remove_clicked()
{
    emit _click(ABOUTORGAN::remove);
}



void aboutorganization::on_description_textChanged()
{
    if(curOrgan.role == "manager"){
        ui->edit->show();
    }
}

