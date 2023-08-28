#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <people.h>
#include <QEnterEvent>
#include <QLayout>
#include <QFont>
#include <QFrame>

enum slotType {
    spl,
    wad,
    pak
};

namespace Ui {
class pauseWidget;
};

class messageBox : public QWidget {
    Q_OBJECT

public:
    explicit messageBox(QWidget *parent = nullptr);
    ~messageBox();
    void setPos(int x, int y);

public slots:
    void showMessage(slotType type, void *ptr);
    void hideMessage();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QString typeText = "类型:";
    QString nameText = "名称:";
    QString rechargeText = "充能延迟:";
    QString delayText = "施放延迟:";
    QString spreadText = "散射角度:";
    QString damageText = "伤害:";
    QString rText = "半径:";
    QString speedText = "速度:";
    QString manaCastText = "法力消耗:";
    QString damageRateText = "伤害倍率:";
    QString speedRateText = "速度倍率:";
    QString lifetimeText = "持续时间:";
    QString capacityText = "容量:";
    QString manaMaxText = "最大法力:";
    QString manaChargeSpeedText = "法力回复速度:";
    QLabel labels[11];
    QFont font;
};

class dragableIcon : public QWidget {
    Q_OBJECT

public:
    explicit dragableIcon(QWidget *parent = nullptr, slotType t = spl, int wandNum = 0, int spellNum = 0, QImage *img = nullptr);
    ~dragableIcon();
    void mousePressEvent(QMouseEvent *event)	override;
    void paintEvent(QPaintEvent *event)			override;

private:
    slotType ty;
    int wandNum;
    int spellNum;
    QImage *img;
};


class backpackSlot : public QWidget
{
    Q_OBJECT

public:
    explicit backpackSlot(QWidget *parent = nullptr, slotType t = spl, people *p = nullptr, int wandNum = 0, int spellNum = 0);
    ~backpackSlot();
    void setPos(int x, int y);
    void setIcon(dragableIcon *d);
    bool hasIcon();
    void clear();

private:
    slotType type;
    int widSpl = 50;
    int heiSpl = 50;
    int widWad = 150;
    int heiWad = 100;
    people *player;
    int wandNum;
    int spellNum;
    dragableIcon *di;
    void dragEnterEvent(QDragEnterEvent *event)	override;
    void dropEvent(QDropEvent *event)			override;
    void paintEvent(QPaintEvent *event) 		override;
    void enterEvent(QEvent *event)		 		override;
    void leaveEvent(QEvent *event)				override;
    QImage gb = QImage("../23su/source/image/garbageBin.png");

signals:
    void dropped();
    void mouseEnter(slotType type, void *ptr);
    void mouseLeave();
};

class pauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pauseWidget(QWidget *parent = nullptr, people *p = nullptr);
    ~pauseWidget();
    void setPlayer(people *p);

protected:
    people *player;
    void paintEvent(QPaintEvent *event)	override;

private:
    Ui::pauseWidget *ui;
    backpackSlot **wand1;
    backpackSlot ***wandSpells1;
    backpackSlot **backpackSpells;
    backpackSlot *garbageBin;
    messageBox *msg;
    QTimer *timer;

};

#endif // PAUSEWIDGET_H
