#ifndef BEGINWIDGET_H
#define BEGINWIDGET_H

#include <QWidget>
#include <QPainter>
#include<QLabel>
#include<QPushButton>
#include<QKeyEvent>
#include <QEvent>
class beginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit beginWidget(QWidget *parent = nullptr);
    ~beginWidget();
signals:
    void ok();
private:
    void paintEvent(QPaintEvent *event)			override;
    void keyPressEvent(QKeyEvent *event)        override;
    void mousePressEvent(QMouseEvent *event)    override;
    QImage backgroundImg ;
};


#endif // BEGINWIDGET_H
