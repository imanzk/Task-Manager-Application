#ifndef RECOVERY_H
#define RECOVERY_H

#include <QWidget>
#include <generics.h>

namespace Ui {
class recovery;
}

class recovery : public QWidget
{
    Q_OBJECT

public:
    explicit recovery(QWidget *parent = nullptr);
    ~recovery();
    void display(QString);

private slots:
    void on_btn_clicked();
signals:
    void _click(User);
private:
    Ui::recovery *ui;
};

#endif // RECOVERY_H
