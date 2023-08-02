#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include"mywidget.h"

namespace Ui {
class loginwidget;
}

class loginwidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginwidget(QWidget *parent = 0);
    ~loginwidget();

private slots:
    void on_button2_clicked();

private:
    Ui::loginwidget *ui;
    myWidget w;
};

#endif // LOGINWIDGET_H
