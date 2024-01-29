#ifndef ARCHIVED_H
#define ARCHIVED_H

#include <QWidget>

namespace Ui {
class archived;
}

class archived : public QWidget
{
    Q_OBJECT

public:
    explicit archived(QWidget *parent = nullptr);
    ~archived();

private:
    Ui::archived *ui;
};

#endif // ARCHIVED_H
