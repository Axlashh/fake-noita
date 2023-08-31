#include "rewardwidget.h"

chosenIcon::chosenIcon(QWidget *parent, int num, void *ptr, slotType type) :
    QWidget(parent),
    ptr(ptr),
    num(num),
    type(type)
{
}

chosenIcon::~chosenIcon() {}

void chosenIcon::setPos(int x, int y) {
    if (type == slotType::spl)
        setGeometry(x, y, 80, 80);
    else
        setGeometry(x, y, 150, 150);
}

void chosenIcon::paintEvent(QPaintEvent *event) {
    if (type == slotType::spl)
        img = *reinterpret_cast<class::spell*>(ptr)->getimg();
    else
        img = reinterpret_cast<wand*>(ptr)->img;
    QPainter painter(this);
    QSize imageSize = img.size();
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
    painter.drawImage(tr, img);
}

void chosenIcon::mousePressEvent(QMouseEvent *event) {
    emit mousePress(num);
}

void chosenIcon::enterEvent(QEvent *event) {
    emit mouseEnter(type, ptr);
}

void chosenIcon::leaveEvent(QEvent *event) {
    emit mouseLeave();
}

rewardWidget::rewardWidget(QWidget *parent, people *player, slotType type) :
    QWidget(parent),
    player(player),
    type(type)
{
    setGeometry(0, 0, parent->width(), parent->height());

    QFont font;
    font.setFamily("IPix");
    font.setPointSize(16);

    errorMsg = new QLabel(this);
    errorMsg->setGeometry(450, 600, 500, 50);
    errorMsg->setFont(font);

    //定义主信息
    mainMsg = new QLabel(this);
    mainMsg->setGeometry(450, 20, 400, 100);
    mainMsg->setFont(font);
    if (type == slotType::spl)
        mainMsg->setText("挑选一个法术加入你的背包");
    else
        mainMsg->setText("挑选一个法杖加入你的背包");
    msg = new messageBox(this);
    msg->setPos(800, 100);

    if (type == slotType::spl) {
        //定义跳过按钮
        exitButton = new QPushButton(this);
        exitButton->setGeometry(550, 700, 130, 50);
        exitButton->setText("跳过");
        exitButton->setFont(font);
        connect(exitButton, &QPushButton::clicked, this, &rewardWidget::onExitButtonClicked);
    }

    if (type == slotType::spl) {
        for (int i = 0; i < 3; i++) {
            ic[i] = new chosenIcon(this, i);
            ic[i]->setPos(100, 200 + 120 * i);
            connect(ic[i], &chosenIcon::mouseEnter, msg, &messageBox::showMessage);
            connect(ic[i], &chosenIcon::mouseLeave, msg, &messageBox::hideMessage);
            connect(ic[i], &chosenIcon::mousePress, this, &rewardWidget::clicked);
        }
    } else {
        ic[0] = new chosenIcon(this, 0, new shortWand(), slotType::wad);
        ic[1] = new chosenIcon(this, 1, new longWand(), slotType::wad);
        ic[0]->setPos(100, 200);
        ic[1]->setPos(100, 500);
        for (int i = 0; i < 2; i++) {
            connect(ic[i], &chosenIcon::mouseEnter, msg, &messageBox::showMessage);
            connect(ic[i], &chosenIcon::mouseLeave, msg, &messageBox::hideMessage);
            connect(ic[i], &chosenIcon::mousePress, this, &rewardWidget::clicked);
        }
    }
}

rewardWidget::~rewardWidget()
{
    for (int i = 0; i < 3; i++) delete ic[i];
    delete msg;
    delete errorMsg;
    delete mainMsg;
    delete exitButton;
}

void rewardWidget::myUpdate() {
    for (int i = 0; i < 3; i++) {
        class::spell *tp = reinterpret_cast<class::spell*>(ic[i]->ptr);
        if (tp != nullptr) {
            delete tp;
        }
        ic[i]->ptr = nullptr;
        int ts = rand() % 100;
        class::spell *spl = nullptr;
        if (ts <= 20) {
            spl = new sparkBolt();
        } else if (ts <= 30) {
            spl = new sparkBoltt();
        } else if (ts <= 45){
            spl = new energyOrb();
        } else if (ts <= 50) {
            spl = new energyOrbt();
        } else if (ts <= 60) {
            spl = new chain();
        } else if (ts <= 70) {
            spl = new doubleSpell();
        } else if (ts <= 80) {
            spl = new addMana();
        } else if (ts <= 90) {
            spl = new speedUp();
        } else {
            spl = new damagePlus();
        }
        ic[i]->ptr = spl;
    }
    errorMsg->setText("");
}

void rewardWidget::clicked(int num) {
    if (type == slotType::spl) {
        class::spell *tp = reinterpret_cast<class::spell*>(ic[num]->ptr);
        if (player->addSpell(tp)) {
            ic[num]->ptr = nullptr;
            for (int i = 0; i < 3; i++) {
                if (i == num) continue;
                delete reinterpret_cast<class::spell*>(ic[i]->ptr);
                ic[i]->ptr = nullptr;
            }
            this->hide();
            emit ok();
        } else {
            errorMsg->setText("背包已满，请放弃选择");
        }
    } else {
        player->addWand(reinterpret_cast<wand*>(ic[num]->ptr), 1);
        delete reinterpret_cast<wand*>(ic[1 - num]->ptr);
        this->hide();
        emit ok();
    }
}

void rewardWidget::onExitButtonClicked() {
    for (int i = 0; i < 3; i++) {
        delete reinterpret_cast<class::spell*>(ic[i]->ptr);
        ic[i]->ptr = nullptr;
    }
    this->hide();
    emit ok();
}

void rewardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0x2c, 0x3e, 0x50));
    if (type == slotType::spl)
        for (int i = 0; i < 3; i++) ic[i]->show();
    else
        for (int i = 0; i < 2; i++) ic[i]->show();
}
