#ifndef DEADWIDGET_H
#define DEADWIDGET_H

#include <QWidget>
#include <QPainter>
#include<QLabel>
#include<QPushButton>
class deadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit deadWidget(QWidget *parent = nullptr);
    ~deadWidget();

private:
    void paintEvent(QPaintEvent *event)			override;
    QImage backgroundImg ;
    QLabel *deadLabel;
    QPushButton *deadButton;
};

#endif // DEADWIDGET_H
