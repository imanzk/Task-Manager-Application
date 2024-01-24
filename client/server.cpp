#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::server)
{
    ui->setupUi(this);
}

server::~server()
{
    delete ui;
}

void server::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString str = item->text();
}

