#include "gameWidget.h"
#include "ui_gameWidget.h"
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>
#include <qnamespace.h>

gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    initializeWorld();
    playerImg = (new QImage("../23su/source/image/player.jpg"))->mirrored(true, true);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        world->Step(1.0f / 60.0f, 6, 2);
        update();
        playerMove();
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

    //绘制人物
    painter.drawImage(QRectF(QPointF(player->getPos().x * PPM - player->getSize().x * PPM, player->getPos().y * PPM - player->getSize().y * PPM),
                             QPointF(player->getPos().x * PPM + player->getSize().x * PPM, player->getPos().y * PPM + player->getSize().y * PPM)), playerImg);
    printf("%f, %f, %f, %f, %f\n", player->getSize().x, player->getSize().y, player->getPos().x, player->getPos().y, ground->GetPosition().y);

    //绘制jump框
    painter.fillRect(QRect(0, height() - 20, player->jump, 20), Qt::yellow);
}

void gameWidget::initializeWorld() {
    b2Vec2 gravity(0, -9.8f);
    world = new b2World(gravity);
    createPlayer();
    createMap();
    playerContactListener *pcl = new playerContactListener();
    pcl->player = player;
    world->SetContactListener(pcl);
}

void gameWidget::createPlayer() {
    //创建人物的基本属性
    b2BodyDef playerDef;
    b2Vec2 pos(10.0f, 20.0f);
    b2BodyUserData t;
    t.pointer = (uintptr_t)"player";
    playerDef.allowSleep = false;
    playerDef.type = b2_dynamicBody;
    playerDef.position = pos;
    playerDef.fixedRotation = true;
    playerDef.userData = t;

    //创建人物的形状
    b2PolygonShape playerShape;
    playerShape.SetAsBox(0.5f, 1.0f);

    //定义人物特征
    b2FixtureDef playerFix;
    playerFix.shape = &playerShape;	//形状
    playerFix.friction = 0.5;		//摩擦系数
    playerFix.restitution = 0; 	//弹性
    playerFix.density = 30;			//密度
    playerFix.isSensor = false;


    player = new people(&playerDef, &playerFix, world);
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
            player->addForce(b2Vec2(0, 600 + (player->maxySpeed - (yv > 0 ? yv : 0)) * 100));
            player->jump -= 0.5;
            player->onGround = false;
        }
    } else if (player->jump < 100){
        if (player->onGround) player->jump += 1.5;
        else player->jump += 0.1;
    }
}

void gameWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = true;
}

void gameWidget::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = false;
}

void playerContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();

    if (((const char *)bodyA->GetUserData().pointer == std::string("player") && bodyA->GetPosition().y > bodyB->GetPosition().y) ||
        ((const char *)bodyB->GetUserData().pointer == std::string("player") && bodyB->GetPosition().y > bodyA->GetPosition().y)) {
        player->onGround = true;
    }
}
