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

private:
    Ui::loginWidget *ui;
    gameWidget w;
};

#endif // LOGINWIDGET_H
