#include "beginWidget.h""
#include<QDebug>
beginWidget::beginWidget(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(parent->rect());
    backgroundImg = QImage("../23su/source/image/background.png").mirrored(false,false);

    QFont font;
    font.setFamily("IPix");
    font.setPointSize(96);
    this->grabKeyboard();

}

void beginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(rect(), backgroundImg);
}

void beginWidget::keyPressEvent(QKeyEvent *event)
{
    emit ok();
    this->hide();
}

void beginWidget::mousePressEvent(QMouseEvent *event)
{
    emit ok();
    this->hide();
}

beginWidget::~beginWidget()
{
}
