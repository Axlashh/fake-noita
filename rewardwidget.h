#ifndef REWARDWIDGET_H
#define REWARDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "spell.h"
#include "wand.h"
#include "people.h"
#include "pauseWidget.h"

class chosenIcon : public QWidget
{
    Q_OBJECT
public:
    explicit chosenIcon(QWidget *parent = nullptr);
    ~chosenIcon();
};

class rewardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit rewardWidget(QWidget *parent = nullptr, people *player = nullptr);
    ~rewardWidget();

protected:
    chosenIcon *ic[3];
    people *player;
    void paintEvent(QPaintEvent *event)	override;
};

#endif // REWARDWIDGET_H
