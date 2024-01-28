#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "generics.h"

namespace Ui {
class home;
}
enum HOME{create , tasks , logout , organclick , filter , sort};


class home : public QWidget
{
    Q_OBJECT
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QString filter = "member";
signals:
    void _click(HOME ,Organization = Organization());
public:
    explicit home(QWidget *parent = nullptr);
    ~home();
    void display(Organization);

private slots:
    void on_logout_clicked();

    void on_tasks_clicked();

    void on_create_clicked();

    void on_filter_clicked();

    void on_sort_clicked();

private:
    Ui::home *ui;
};

#endif // HOME_H
