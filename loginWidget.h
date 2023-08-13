#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "gameWidget.h"
#include "ui_gameWidget.h"

namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginWidget(QWidget *parent = 0);
    ~loginWidget();

private slots:

    void on_registerButton_clicked();

    void on_loginButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::loginWidget *ui;
    gameWidget w;
};

#endif // LOGINWIDGET_H
