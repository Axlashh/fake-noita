#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <people.h>

enum slotType {
    spl,
    wad,
    pak
};

namespace Ui {
class pauseWidget;
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
    int wandNum;
    int spellNum;
    people *player;
    dragableIcon *di;
    void dragEnterEvent(QDragEnterEvent *event)	override;
    void dropEvent(QDropEvent *event)			override;
    void paintEvent(QPaintEvent *event) 		override;

signals:
    void dropped();
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
    QTimer *timer;

};

#endif // PAUSEWIDGET_H
