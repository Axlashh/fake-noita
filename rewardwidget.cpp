#include "rewardwidget.h"

chosenIcon::chosenIcon(QWidget *parent) :
    QWidget(parent)
{

}

chosenIcon::~chosenIcon() {}

rewardWidget::rewardWidget(QWidget *parent, people *player) :
    QWidget(parent),
    player(player)
{

}

rewardWidget::~rewardWidget()
{

}

void rewardWidget::paintEvent(QPaintEvent *event)
{

}
