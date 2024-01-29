#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>

namespace Ui {
class project;
}

class project : public QWidget
{
    Q_OBJECT

public:
    explicit project(QWidget *parent = nullptr);
    ~project();

private:
    Ui::project *ui;
};

#endif // PROJECT_H
