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
    explicit chosenIcon(QWidget *parent = nullptr, int num = 0, class::spell *spl = nullptr);
    ~chosenIcon();
    void setPos(int x, int y);
    class::spell *sp;


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

class rewardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit rewardWidget(QWidget *parent = nullptr, people *player = nullptr);
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
    void paintEvent(QPaintEvent *event)	override;


signals:
    void ok();
};

#endif // REWARDWIDGET_H
