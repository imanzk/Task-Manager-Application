#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "generics.h"


namespace Ui {
class home;
enum HOME{create , tasks , logout , organclick , filter , sort};
}
using Ui::HOME;


class home : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QVector<Organization> list;
signals:
    void _click(HOME ,Organization = Organization());
public:
    bool sort = false;
    QString filter = "all";
    explicit home(QWidget *parent = nullptr);
    ~home();
    void display(Organization);
    void displayButton(Organization);
private slots:
    void on_logout_clicked();

    void on_tasks_clicked();

    void on_create_clicked();

    void on_filter_clicked();

    void on_sort_clicked();
public slots:
    void on_organclick();

private:
    Ui::home *ui;
};

#endif // HOME_H
