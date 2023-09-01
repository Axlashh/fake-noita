#include "deadwidget.h"


deadWidget::deadWidget(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(parent->rect());
    backgroundImg = QImage("../23su/source/image/background.png").mirrored(false,false);
    QFont font;
    font.setFamily("IPix");
    font.setPointSize(96);
    deadLabel = new QLabel(this);
    deadLabel->setFont(font);
    deadLabel->setStyleSheet("color:rgb(255,0,0)");
    deadLabel->setText("你死了!");
    deadLabel->setGeometry(width()/2-300,height()/2-400,800,800);

    deadButton= new QPushButton(this);
    deadButton->setGeometry(550, 700, 130, 50);
    font.setPointSize(16);
    deadButton->setText("退出");
    deadButton->setFont(font);
    connect(deadButton, &QPushButton::clicked, parent, &QWidget::hide);
}

void deadWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(rect(), backgroundImg);
}

deadWidget::~deadWidget()
{
    delete deadLabel;
}
