#include "pauseWidget.h"
#include "ui_pauseWidget.h"
#include <QPainter>

pauseWidget::pauseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pauseWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0, 0, parent->width(), parent->height());
}

pauseWidget::~pauseWidget()
{
    delete ui;
}

void pauseWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 150));
}
