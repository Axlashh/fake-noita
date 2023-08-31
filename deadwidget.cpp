#include "deadwidget.h"


deadWidget::deadWidget(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(parent->rect());
}

void deadWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0xff, 0xff, 0xff));
}

deadWidget::~deadWidget()
{}
