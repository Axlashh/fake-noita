#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "func.h"

namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget(QWidget *parent = 0);
    ~gameWidget();

private slots:


private:
    Ui::gameWidget *ui;
};

#endif // GAMEWIDGET_H

