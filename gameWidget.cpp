#include "gameWidget.h"
#include "ui_gameWidget.h"
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>

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
    painter.drawImage(QRectF(QPointF(player->getPos().x * PPM, player->getPos().y * PPM),
                             QPointF(player->getPos().x * PPM + player->getSize().x*PPM, player->getPos().y * PPM + player->getSize().y*PPM)), playerImg);
    printf("%f, %f, %f, %f, %f\n", player->getSize().x, player->getSize().y, player->getPos().x, player->getPos().y, ground->GetPosition().y);
}

void gameWidget::initializeWorld() {
    b2Vec2 gravity(0, -9.8f);
    world = new b2World(gravity);
    createPlayer();
    createMap();
}

void gameWidget::createPlayer() {
    //创建人物的基本属性
    b2BodyDef playerDef;
    b2Vec2 pos(10.0f, 20.0f);
    playerDef.allowSleep = false;
    playerDef.type = b2_dynamicBody;
    playerDef.position = pos;

    //创建人物的形状
    b2PolygonShape playerShape;
    playerShape.SetAsBox(0.5, 1);

    //定义人物特征
    b2FixtureDef playerFix;
    playerFix.shape = &playerShape;	//形状
    playerFix.friction = 0.5;		//摩擦系数
    playerFix.restitution = 0.5; 	//弹性
    playerFix.density = 30;			//密度
    playerFix.isSensor = false;

    player = new people(&playerDef, &playerFix, world);
}

void gameWidget::createMap() {
    b2BodyDef gd;
    gd.position.Set(0, 5);
    gd.type = b2_staticBody;

    ground = world->CreateBody(&gd);

    b2EdgeShape gdS;
    gdS.SetTwoSided(b2Vec2(0, 5), b2Vec2(1000, 5));

    ground->CreateFixture(&gdS, 0);
}
