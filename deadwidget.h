#ifndef DEADWIDGET_H
#define DEADWIDGET_H

#include <QWidget>
#include <QPainter>
#include<QMessageBox>
class deadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit deadWidget(QWidget *parent = nullptr);
    ~deadWidget();

private:
    void paintEvent(QPaintEvent *event)			override;
};

#endif // DEADWIDGET_H
