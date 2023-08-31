#ifndef REWARDWIDGET_H
#define REWARDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include "spell.h"
#include "wand.h"
#include "people.h"
#include "pauseWidget.h"

class chosenIcon : public QWidget
{
    Q_OBJECT
public:
    explicit chosenIcon(QWidget *parent = nullptr, int num = 0, void *ptr = nullptr, slotType type = slotType::spl);
    ~chosenIcon();
    void setPos(int x, int y);
    void *ptr;

private:
    int num;
    slotType type;
    QImage img;

    void paintEvent(QPaintEvent *event)			override;
    void mousePressEvent(QMouseEvent *event)	override;
    void enterEvent(QEvent *event)				override;
    void leaveEvent(QEvent *event)				override;



signals:
    void mousePress(int num);
    void mouseEnter(slotType type, void *spl);
    void mouseLeave();
};

class rewardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit rewardWidget(QWidget *parent = nullptr, people *player = nullptr, slotType type = slotType::spl);
    ~rewardWidget();
    void myUpdate();

public slots:
    void clicked(int num);

private slots:
    void onExitButtonClicked();

protected:
    chosenIcon *ic[3];
    messageBox *msg;
    QLabel *errorMsg;
    QLabel *mainMsg;
    QPushButton *exitButton;
    people *player;
    slotType type;
    void paintEvent(QPaintEvent *event)	override;


signals:
    void ok();
};

#endif // REWARDWIDGET_H
