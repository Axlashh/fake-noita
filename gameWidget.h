#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include "others.h"

namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget(QWidget *parent = 0);
    ~gameWidget();
    Ui::gameWidget *ui;

private slots:


private:

};

#endif // GAMEWIDGET_H

