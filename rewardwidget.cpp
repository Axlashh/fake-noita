#include "rewardwidget.h"

chosenIcon::chosenIcon(QWidget *parent, int num, class::spell *spl) :
    QWidget(parent),
    sp(spl),
    num(num)
{
}

chosenIcon::~chosenIcon() {}

void chosenIcon::setPos(int x, int y) {
    setGeometry(x, y, 80, 80);
}

void chosenIcon::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QSize imageSize = sp->getimg()->size();
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
    painter.drawImage(tr, *sp->getimg());
}

void chosenIcon::mousePressEvent(QMouseEvent *event) {
    emit mousePress(num);
}

void chosenIcon::enterEvent(QEvent *event) {
    emit mouseEnter(slotType::spl, sp);
}

void chosenIcon::leaveEvent(QEvent *event) {
    emit mouseLeave();
}

rewardWidget::rewardWidget(QWidget *parent, people *player) :
    QWidget(parent),
    player(player)
{
    setGeometry(0, 0, parent->width(), parent->height());

    QFont font;
    font.setFamily("SimHei");
    font.setPointSize(16);

    errorMsg = new QLabel(this);
    errorMsg->setGeometry(450, 600, 500, 50);
    errorMsg->setFont(font);

    //定义主信息
    mainMsg = new QLabel(this);
    mainMsg->setGeometry(450, 50, 400, 100);
    mainMsg->setFont(font);
    mainMsg->setText("挑选一个法术加入你的背包");
    msg = new messageBox(this);
    msg->setPos(800, 100);

    //定义跳过按钮
    exitButton = new QPushButton(this);
    exitButton->setGeometry(550, 700, 100, 30);
    exitButton->setText("跳过");
    connect(exitButton, &QPushButton::clicked, this, &rewardWidget::onExitButtonClicked);

    for (int i = 0; i < 3; i++) {
        ic[i] = new chosenIcon(this, i);
        ic[i]->setPos(100, 200 + 120 * i);
        connect(ic[i], &chosenIcon::mouseEnter, msg, &messageBox::showMessage);
        connect(ic[i], &chosenIcon::mouseLeave, msg, &messageBox::hideMessage);
        connect(ic[i], &chosenIcon::mousePress, this, &rewardWidget::clicked);
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
        if (ic[i]->sp != nullptr) {
            delete ic[i]->sp;
            ic[i]->sp = nullptr;
        }
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
        ic[i]->sp = spl;
    }
}

void rewardWidget::clicked(int num) {
    if (player->addSpell(ic[num]->sp)) {
        ic[num]->sp = nullptr;
        for (int i = 0; i < 3; i++) {
            if (i == num) continue;
            delete ic[i]->sp;
            ic[i]->sp = nullptr;
        }
        this->hide();
        emit ok();
    } else {
        errorMsg->setText("背包已满，请放弃选择");
    }
}

void rewardWidget::onExitButtonClicked() {
    for (int i = 0; i < 3; i++) {
        delete ic[i]->sp;
        ic[i]->sp = nullptr;
    }
    this->hide();
    emit ok();
}

void rewardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0x2c, 0x3e, 0x50));
    for (int i = 0; i < 3; i++) ic[i]->show();
}
