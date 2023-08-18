#include "gameWidget.h"
#include "ui_gameWidget.h"
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>
#include <qnamespace.h>
#include <cmath>
#include "pausewidget.h"

gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    isPaused = false;
    initializeWorld();
    wand* aaaa = new normalWand();
    class::spell *bbb = new sparkBolt();
    aaaa->addSpell(bbb, 0);
    aaaa->addSpell(bbb->copy(), 1);
    player->addWand(aaaa, 0);
    this->menu = new pauseWidget(this, player);
    menu->hide();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        if (!isPaused) {
        myUpdate();
        update();
        }
    });
    timer->start(1000 / 60); // 设置更新频率为 60 Hz

}

gameWidget::~gameWidget()
{
    delete ui;
}

void gameWidget::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    painter.translate(0, height());
    painter.scale(1, -1);

    painter.setRenderHint(QPainter::Antialiasing, true);

    // 清空背景
    painter.fillRect(rect(), Qt::white);

    // 绘制地面
    painter.setPen(Qt::black);
    painter.drawLine(0, ground->GetPosition().y * PPM, width(), ground->GetPosition().y * PPM);

    //绘制世界中的人物和法术
    for (auto it = world->GetBodyList(); it != nullptr; it = it->GetNext()) {
        struct::userData* ud = reinterpret_cast<struct::userData*>(it->GetUserData().pointer);
        switch (ud->type) {
        case userDataType::player:
            reinterpret_cast<people*>(ud->p)->draw(&painter, PPM);
            break;
        case userDataType::spell:
            reinterpret_cast<class::spell*>(ud->p)->draw(&painter, PPM);
            break;

        default:
            break;
        }
    }

    //绘制法杖
    auto tw = player->getWand(player->wandInHand);
    if (tw != nullptr) {
        painter.save();
        painter.translate(player->getPos().x * PPM, player->getPos().y * PPM);
        painter.rotate(degree);
        painter.drawImage(QRectF(QPointF(0, -0.2 * PPM), QPointF(1.2 * PPM, 0.2 * PPM)), tw->img);
        painter.restore();
        painter.fillRect(QRect(0, height() - 40, tw->getMana(), 20), Qt::blue);
        painter.fillRect(QRect(0, height() - 60, tw->getRecharge(), 20), Qt::red);
        painter.fillRect(QRect(0, height() - 80, tw->getDelay(), 20), Qt::yellow);
    }

    //绘制jump框
    painter.fillRect(QRect(0, height() - 20, player->jump, 20), Qt::yellow);
}

void gameWidget::initializeWorld() {
    b2Vec2 gravity(0, -9.8f);
    world = new b2World(gravity);

    //创建玩家
    b2Vec2 pos(10.0f, 20.0f);
    player = new people(world, pos);

    createMap();
    playerContactListener *pcl = new playerContactListener();
    pcl->player = player;
    world->SetContactListener(pcl);
}

void gameWidget::createMap() {
    b2BodyDef gd;
    gd.position = b2Vec2(0, 0);
    gd.type = b2_staticBody;
    b2BodyUserData t;
    t.pointer = (uintptr_t)"ground";
    gd.userData = t;

    ground = world->CreateBody(&gd);

    b2EdgeShape gdS;
    gdS.SetTwoSided(b2Vec2(0, 0), b2Vec2(800, 0));

    ground->CreateFixture(&gdS, 0);
}

void gameWidget::myUpdate() {
    //获取此帧鼠标的角度
    radian = std::atan2(height() - mousePos.y() - player->getPos().y * PPM, mousePos.x() - player->getPos().x * PPM);
    degree = radian * (180.0 / M_PI);

    //计算人物移动
    playerMove();

    wandUpdate();
    world->Step(1.0f / 60.0f, 6, 2);
}

void gameWidget::wandUpdate() {
    //对玩家的每根法杖进行更新
    for (int i = 0; i < player->maxWand; i++) {
        if (player->getWand(i) != nullptr) {
            player->getWand(i)->update();
        }
    }

    auto wd = player->getWand(player->wandInHand);
    //如果鼠标左键被按下，发射！
    if (isPressed[26] && wd->readyToShoot()) {
        float cs = cos(radian), sn = sin(radian), xx = player->getPos().x, yy = player->getPos().y;
        wd->shoot(xx + 1.2 * cs, yy + 1.2 * sn, degree, world);
    }
}

void gameWidget::playerMove() {
    float xv = player->getSpeed().x;
    if (isPressed[0]) {
        if (xv >= -player->maxxSpeed) {
            if (xv > 0) player->addForce(b2Vec2(-1000, 0));
            player->addForce(b2Vec2(-1000, 0));
        } else {
        }
    }
    if (isPressed[3]) {
        if (xv <= player->maxxSpeed) {
            if (xv < 0) player->addForce(b2Vec2(1000, 0));
            player->addForce(b2Vec2(1000, 0));
        } else {
        }
    }
    if (isPressed['w' - 'a']) {
        if (player->jump > 0) {
            float yv = player->getSpeed().y;
            player->addForce(b2Vec2(0, 600 + (player->maxySpeed - (yv > 0 ? yv : 0)) * 300));
            player->jump -= 0.5;
            player->onGround = false;
        }
    } else if (player->jump < 100){
        if (player->onGround) player->jump += 3;
        else player->jump += 0.1;
    }
}

void gameWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = true;
    if (key == Qt::Key_Escape) {
        if (isPaused) {
            menu->hide();
            isPaused = false;
        } else {
            menu->show();
            isPaused = true;
        }
    }
}

void gameWidget::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = false;
}

void gameWidget::mousePressEvent(QMouseEvent *event) {
    isPressed[26] = true;
}

void gameWidget::mouseReleaseEvent(QMouseEvent *event) {
    isPressed[26] = false;
}

void gameWidget::mouseMoveEvent(QMouseEvent *event) {
    setMouseTracking(true);
    mousePos = event->pos();
}

void playerContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();
    userData* udA = reinterpret_cast<userData*>(bodyA->GetUserData().pointer);
    userData* udB = reinterpret_cast<userData*>(bodyB->GetUserData().pointer);

    if ((udA->type == userDataType::player && bodyA->GetPosition().y > bodyB->GetPosition().y) ||
        (udB->type == userDataType::player && bodyB->GetPosition().y > bodyA->GetPosition().y)) {
        player->onGround = true;
    }
}
