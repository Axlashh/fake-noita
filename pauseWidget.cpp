#include "pauseWidget.h"
#include "ui_pauseWidget.h"
#include <QPainter>

backpackSlot::backpackSlot(QWidget *parent, slotType t, people *p) :
    QWidget(parent),
    type(t),
    player(p)
{
    setAcceptDrops(true);
}

backpackSlot::~backpackSlot() {

}

void backpackSlot::setPos(int x, int y) {
    if (type == spl)
        this->setGeometry(x, y, widSpl, heiSpl);
    else
        this->setGeometry(x, y, widWad, heiWad);
}

void backpackSlot::dragEnterEvent(QDragEnterEvent *event) {

}

void backpackSlot::dragLeaveEvent(QDragLeaveEvent *event) {

}

void backpackSlot::dragMoveEvent(QDragMoveEvent *event) {

}

void backpackSlot::dropEvent(QDropEvent *event) {

}

void backpackSlot::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (type == spl)
        painter.fillRect(rect(), Qt::white);
    else {
        auto im = player->getWand(0)->img;
        QRectF tr = rect();
        tr.setSize(im.size().scaled(rect().size(),Qt::KeepAspectRatio));
        painter.drawImage(tr, im);

    }
}

pauseWidget::pauseWidget(QWidget *parent, people *p) :
    QWidget(parent),
    player(p),
    ui(new Ui::pauseWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0, 0, parent->width(), parent->height());
    wand1 = new backpackSlot(this, wad, player);
    wand2 = new backpackSlot(this, wad, player);
    wand1->setPos(50, 50);
    wand2->setPos(50, 340);
    wandSpells1 = new backpackSlot*[10];
    wandSpells2 = new backpackSlot*[10];
    backpackSpells = new backpackSlot*[10];
    for (int i = 0; i < 10; i++) {
        wandSpells1[i] = new backpackSlot(this, spl, player);
        wandSpells2[i] = new backpackSlot(this, spl, player);
        backpackSpells[i] = new backpackSlot(this, spl, player);
        wandSpells1[i]->setPos(50 + i * 70, 170);
        wandSpells2[i]->setPos(50 + i * 70, 460);
        backpackSpells[i]->setPos(50 + i * 70, 660);
    }
}

pauseWidget::~pauseWidget()
{
    delete ui;
}

void pauseWidget::setPlayer(people *p) {
    player = p;
}

void pauseWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 150));
}
