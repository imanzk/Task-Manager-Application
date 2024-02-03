#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include <QWidget>

namespace Ui {
class addcomment;
}

class addcomment : public QWidget
{
    Q_OBJECT

public:
    explicit addcomment(QWidget *parent = nullptr);
    ~addcomment();
signals:
    void _click(QString);
private slots:
    void on_edit_clicked();

private:
    Ui::addcomment *ui;
};

#endif // ADDCOMMENT_H
