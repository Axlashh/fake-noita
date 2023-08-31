#ifndef REWARDWIDGETW_H
#define REWARDWIDGETW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include "wand.h"
#include "people.h"
#include "pauseWidget.h"

class chosenIconW : public QWidget
{
    Q_OBJECT
public:
    explicit chosenIconW(QWidget *parent = nullptr, int num = 0, wand *wnd = nullptr);
    ~chosenIconW();
    void setPos(int x, int y);

private:
    int num;

    void paintEvent(QPaintEvent *event)			override;
    void mousePressEvent(QMouseEvent *event)	override;
    void enterEvent(QEvent *event)				override;
    void leaveEvent(QEvent *event)				override;

signals:
    void mousePress(int num);
    void mouseEnter(slotType type, void *spl);
    void mouseLeave();
};

class rewardWidgetW : public QWidget
{
    Q_OBJECT
public:
    explicit rewardWidgetW(QWidget *parent = nullptr, people *player = nullptr);
    ~rewardWidgetW();
    void myUpdate();

public slots:
    void clicked(int num);

private slots:
    void onExitButtonClicked();

protected:
    chosenIconW *ic[2];
    messageBox *msg;
    QLabel *mainMsg;
    QPushButton *exitButton;
    people *player;
    void paintEvent(QPaintEvent *event)	override;


signals:
    void ok();
};

#endif // REWARDWIDGETW_H
