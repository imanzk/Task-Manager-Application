#ifndef ABOUTORGANIZATION_H
#define ABOUTORGANIZATION_H

#include <QWidget>
#include "generics.h"
#include <QVBoxLayout>

namespace Ui {
class aboutorganization;
enum ABOUTORGAN{
    edit , remove , addmember , back , memberclick
};
} using Ui::ABOUTORGAN;

class aboutorganization : public QWidget
{
    Q_OBJECT
    QVector<User> list;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
public:
    explicit aboutorganization(QWidget *parent = nullptr);
    ~aboutorganization();
    Organization curOrgan;
    void displayOrgan(Organization org);
    void display(User);
    void displayMember(User);
signals:
    void _click(ABOUTORGAN,Organization=Organization());
public slots:

    void on_addmember_clicked();

    void on_back_clicked();
    void on_memberclicked();

    void on_edit_clicked();

    void on_type_textEdited(const QString &arg1);

private slots:
    void on_remove_clicked();

    void on_description_textChanged();


private:
    Ui::aboutorganization *ui;
};

#endif // ABOUTORGANIZATION_H
