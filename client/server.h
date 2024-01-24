#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::server *ui;
};

#endif // SERVER_H
