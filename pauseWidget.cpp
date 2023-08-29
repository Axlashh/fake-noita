#include "pauseWidget.h"
#include "ui_pauseWidget.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>

bool upd = true;

messageBox::messageBox(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(QRect(0, 0, 480, 650));
    for (int i = 0; i < 11; i++) {
        mainLayout->addWidget(labels + i);
    }
    this->setLayout(mainLayout);
    font.setFamily("IPix");
    font.setPointSize(14); // 设置字体大小
    font.setBold(true);    // 设置字体粗细
    for (int i = 0; i < 11; i++) {
        labels[i].setFont(font);
    }
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0x7d, 0x8e, 0x95, 200));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    this->hide();
}

messageBox::~messageBox() {
    delete mainLayout;
}

void messageBox::setPos(int x, int y) {
    this->move(x, y);
}

void messageBox::showMessage(slotType type, void *ptr) {
    if (ptr == nullptr) {
        this->hide();
        return;
    }
    wand *wt;
    class::spell *st;
    switch (type) {
    case wad:
        wt = reinterpret_cast<wand*>(ptr);
        labels[0].setText(typeText + "法杖");
        labels[1].setText(nameText + wt->getName());
        labels[2].setText(rechargeText + QString::number((float) wt->getBRecharge() / 60.0f, 'f', 2) + "s");
        labels[3].setText(delayText + QString::number((float) wt->getBDelay() / 60.0f, 'f', 2) + "s");
        labels[4].setText(spreadText + QString::number(wt->getSpread()));
        labels[5].setText(capacityText + QString::number(wt->getCapacity()));
        labels[6].setText(manaMaxText + QString::number(wt->getMaxMana()));
        labels[7].setText(manaChargeSpeedText + QString::number(wt->getManaChargeSpeed()));
        labels[8].setText(wt->getExtraInfo());
        for (int i = 9; i < 11; i++) {
            labels[i].clear();
        }
        break;

    case spl:
        st = reinterpret_cast<class::spell*>(ptr);
        labels[0].setText(typeText + "法术");
        labels[1].setText(nameText + st->getName());
        labels[2].setText(rechargeText + QString::number((float) st->getRechargeTime() / 60.0f, 'f', 2) + "s");
        labels[3].setText(delayText + QString::number((float) st->getDelay() / 60.0f, 'f', 2) + "s");
        labels[4].setText(manaCastText + QString::number(st->getManaCast()));
        switch (st->getType()) {
        case projectile:
        case withTrigger:
            labels[5].setText(spreadText + QString::number(st->getSpread()));
            labels[6].setText(damageText + QString::number(st->getDamage()));
            labels[7].setText(lifetimeText + QString::number((float) st->getLifetime() / 60.0f, 'f', 2) + "s");
            labels[8].setText(rText + QString::number(st->getR()));
            labels[9].setText(speedText + QString::number(st->getSpeed()));
            labels[10].setText(st->getExtraInfo());
            break;
        case multicast:
            labels[5].setText(st->getExtraInfo());
            for (int i = 6; i < 11; i++) {
                labels[i].clear();
            }
            break;
        case pmodifier:
            labels[5].setText(speedRateText + QString::number(st->getSpeedRate(), 'f', 2));
            labels[6].setText(damageRateText + QString::number(st->getDamageRate(), 'f', 2));
            labels[7].setText(st->getExtraInfo());
            for (int i = 8; i < 11; i++) {
                labels[i].clear();
            }
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
    this->show();
}

void messageBox::hideMessage() {
    this->hide();
}

dragableIcon::dragableIcon(QWidget *parent, slotType t, int wandNum, int spellNum, QImage *img) :
    QWidget(parent),
    ty(t),
    wandNum(wandNum),
    spellNum(spellNum),
    img(img)
{
    setGeometry(parent->rect());
    setMouseTracking(true);
}

void dragableIcon::mousePressEvent(QMouseEvent *event) {
    QDrag *drag = new QDrag(this);
    QMimeData *mimedata = new QMimeData;
    QByteArray ba;
    QDataStream dataStream(&ba, QIODevice::WriteOnly);
    switch(ty) {
    case wad:
        dataStream<<wandNum<<-1;
        mimedata->setData("wand", ba);
        break;
    case spl:
        dataStream<<wandNum<<spellNum;
        mimedata->setData("spell", ba);
        break;
    case pak:
        dataStream<<-1<<wandNum;
        mimedata->setData("backpack", ba);
        break;
    }
    drag->setMimeData(mimedata);
    drag->setPixmap(QPixmap::fromImage(*img));
    drag->setHotSpot(event->pos() - this->pos());
    drag->exec();
}


void dragableIcon::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QSize imageSize = img->size();
    QSize widgetSize = size();
    qreal aspectRatioImage = static_cast<qreal>(imageSize.width()) / imageSize.height();
    qreal aspectRatioWidget = static_cast<qreal>(widgetSize.width()) / widgetSize.height();

    int targetWidth, targetHeight;
    if (aspectRatioImage > aspectRatioWidget) {
        targetWidth = widgetSize.width();
        targetHeight = static_cast<int>(widgetSize.width() / aspectRatioImage);
    } else {
        targetWidth = static_cast<int>(widgetSize.height() * aspectRatioImage);
        targetHeight = widgetSize.height();
    }

    int targetX = (widgetSize.width() - targetWidth) / 2;
    int targetY = (widgetSize.height() - targetHeight) / 2;
    QRectF tr(targetX, targetY, targetWidth, targetHeight);
    painter.drawImage(tr, *img);
}

dragableIcon::~dragableIcon() {
}

backpackSlot::backpackSlot(QWidget *parent, slotType t, people *p, int wandNum, int spellNum) :
    QWidget(parent),
    type(t),
    player(p),
    wandNum(wandNum),
    spellNum(spellNum)
{
    setAcceptDrops(true);
    di = nullptr;
}

backpackSlot::~backpackSlot() {
    if (di != nullptr)
        delete di;

}

void backpackSlot::setPos(int x, int y) {
    if (type == spl || type == pak)
        this->setGeometry(x, y, widSpl, heiSpl);
    else
        this->setGeometry(x, y, widWad, heiWad);
}

void backpackSlot::setIcon(dragableIcon *d) {
    di = d;
}

bool backpackSlot::hasIcon() {
    return di != nullptr;
}

void backpackSlot::clear() {
    if (di != nullptr) {
        delete di;
        di = nullptr;
    }
}

void backpackSlot::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData *md = event->mimeData();
    if (event->source()->parent() != this && ((this->type == wad && md->hasFormat("wand")) || ((this->type == spl || this->type == pak) && (md->hasFormat("spell") || md->hasFormat("backpack"))))) {
        event->accept();
    } else {
        event->ignore();
    }
}

void backpackSlot::dropEvent(QDropEvent *event) {
    const QMimeData *md = event->mimeData();
    int wand1, wand2, spell1, spell2;
    switch (type) {
    case wad:
        wand2 = wandNum;
        spell2 = -1;
        break;
    case spl:
        wand2 = wandNum;
        spell2 = spellNum;
        break;
    case pak:
        wand2 = -1;
        spell2 = wandNum;
        break;
    }
    QString tp;
    if (md->hasFormat("wand"))
        tp = "wand";
    else if (md->hasFormat("spell"))
        tp = "spell";
    else if (md->hasFormat("backpack"))
        tp = "backpack";
    QByteArray ba = md->data(tp);
    QDataStream qds(&ba, QIODevice::ReadOnly);
    qds>>wand1>>spell1;
    player->swap(wand1, wand2, spell1, spell2);
    emit dropped();
    upd = true;
}

void backpackSlot::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (di != nullptr) {
        di->show();
    }
    else {
        if (wandNum == 10)
            painter.drawImage(rect(), gb);
        else
            painter.fillRect(rect(), Qt::white);
    }
}

void backpackSlot::enterEvent(QEvent *event) {
    switch (type) {
    case wad:
        emit mouseEnter(wad, player->getWand(wandNum));
        break;

    case spl:
        emit mouseEnter(spl, player->getWand(wandNum)->getSpell(spellNum));
        break;

    case pak:
        emit mouseEnter(spl, player->getPak(wandNum));
        break;

    default:
        break;
    }
}

void backpackSlot::leaveEvent(QEvent *event) {
    emit mouseLeave();
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
    msg = new messageBox(this);
    msg->setPos(800, 100);

    garbageBin = new backpackSlot(this, pak, player, 10);
    garbageBin->setPos(1150, 20);

    wand1 = new backpackSlot*[2];
    wand1[0] = new backpackSlot(this, wad, player, 0);
    wand1[1] = new backpackSlot(this, wad, player, 1);
    wand1[0]->setPos(50, 50);
    wand1[1]->setPos(50, 340);
    wand1[0]->hide();
    wand1[1]->hide();
    connect(wand1[0], &backpackSlot::mouseEnter, msg, &messageBox::showMessage);
    connect(wand1[0], &backpackSlot::mouseLeave, msg, &messageBox::hideMessage);
    connect(wand1[1], &backpackSlot::mouseEnter, msg, &messageBox::showMessage);
    connect(wand1[1], &backpackSlot::mouseLeave, msg, &messageBox::hideMessage);
    wandSpells1 = new backpackSlot**[2];
    wandSpells1[0] = new backpackSlot*[10];
    wandSpells1[1] = new backpackSlot*[10];
    backpackSpells = new backpackSlot*[10];
    for (int i = 0; i < 10; i++) {
        wandSpells1[0][i] = new backpackSlot(this, spl, player, 0, i);
        wandSpells1[1][i] = new backpackSlot(this, spl, player, 1, i);
        backpackSpells[i] = new backpackSlot(this, pak, player, i, 0);
        wandSpells1[0][i]->setPos(50 + i * 70, 170);
        wandSpells1[1][i]->setPos(50 + i * 70, 460);
        backpackSpells[i]->setPos(50 + i * 70, 660);
        wandSpells1[0][i]->hide();
        wandSpells1[1][i]->hide();
        backpackSpells[i]->hide();
        connect(wandSpells1[0][i], &backpackSlot::mouseEnter, msg, &messageBox::showMessage);
        connect(wandSpells1[0][i], &backpackSlot::mouseLeave, msg, &messageBox::hideMessage);
        connect(wandSpells1[1][i], &backpackSlot::mouseEnter, msg, &messageBox::showMessage);
        connect(wandSpells1[1][i], &backpackSlot::mouseLeave, msg, &messageBox::hideMessage);
        connect(backpackSpells[i], &backpackSlot::mouseEnter, msg, &messageBox::showMessage);
        connect(backpackSpells[i], &backpackSlot::mouseLeave, msg, &messageBox::hideMessage);
    }
}

pauseWidget::~pauseWidget()
{
    delete ui;
}

void pauseWidget::myUpdate() {
    upd = true;
}

void pauseWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 150));

    if (upd) {
        for (int i = 0; i < 2; i++) {
            wand* tw = player->getWand(i);
            wand1[i]->clear();
            if (tw != nullptr) {
                dragableIcon *t = new dragableIcon(wand1[i], wad, i, 0, &tw->img);
                wand1[i]->setIcon(t);
                for (int j = 0; j < tw->getSpellNum(); j++) {
                    class::spell *tsp = tw->getSpell(j);
                    wandSpells1[i][j]->clear();
                    if (tsp != nullptr) {
                        dragableIcon *tt = new dragableIcon(wandSpells1[i][j], spl, i, j, tsp->getimg());
                        wandSpells1[i][j]->setIcon(tt);
                    }
                    wandSpells1[i][j]->show();
                }
                for (int j = tw->getSpellNum(); j < 10; j++) {
                    wandSpells1[i][j]->clear();
                    wandSpells1[i][j]->hide();
                }
            }
            wand1[i]->show();
        }

        for (int i = 0; i < 10; i++) {
            class::spell* tw = player->getPak(i);
            backpackSpells[i]->clear();
            if (tw != nullptr) {
                dragableIcon *t = new dragableIcon(backpackSpells[i], pak, i, 0, tw->getimg());
                backpackSpells[i]->setIcon(t);
            }
            backpackSpells[i]->show();
        }

        garbageBin->clear();
        upd = false;
    }
}
