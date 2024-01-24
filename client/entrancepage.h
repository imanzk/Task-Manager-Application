#ifndef ENTRANCEPAGE_H
#define ENTRANCEPAGE_H

#include "generics.h"
#include <QPixmap>

namespace Entrance{
typedef enum TypeKey{login, signup}key_type;
}

namespace Ui {
class welcome;
}

class EntrancePage : public QWidget
{
    Q_OBJECT

public:
    explicit EntrancePage(QWidget *parent = nullptr);
    ~EntrancePage();
private slots:
    void on_Login_pushButton_clicked();
    void on_Signup_pushButton_clicked();
private:
    Ui::welcome *ui;
signals:
    void _click(Entrance::key_type);
};

#endif // ENTRANCEPAGE_H
