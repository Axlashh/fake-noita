#include "others.h"
#include <iostream>

Box2DWidget::Box2DWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1600, 600); // 设置窗口大小
    initializeWorld();      // 初始化 Box2D 物理世界

    // 创建定时器用于更新物理世界和界面
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        world->Step(1.0f / 60.0f, 6, 2);
        update();
    });
    timer->start(1000 / 60); // 设置更新频率为 60 Hz
}

Box2DWidget::~Box2DWidget()
{
    delete world;
}

void Box2DWidget::initializeWorld()
{
    b2Vec2 gravity(0.0f, -9.81f);
    world = new b2World(gravity);
    createGround();
    createBall(400.0f, 100.0f, 1.0f);
}

void Box2DWidget::createGround()
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 10.0f);

    ground = world->CreateBody(&groundBodyDef);

    b2EdgeShape groundBox;
    groundBox.SetTwoSided(b2Vec2(0.0f, 20.0f), b2Vec2(800.0f, 20.0f));
    ground->CreateFixture(&groundBox, 0.0f);
}

void Box2DWidget::createBall(float x, float y, float radius)
{
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(x, y);

    ball = world->CreateBody(&ballBodyDef);

    b2CircleShape circle;
    circle.m_radius = radius;

    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &circle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.friction = 0.3f;
    ballFixtureDef.restitution = 0.7f;

    ball->CreateFixture(&ballFixtureDef);
}

void Box2DWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 清空背景
    painter.fillRect(rect(), Qt::white);

    // 绘制地面
    painter.setPen(Qt::black);
    painter.drawLine(0, height() - ground->GetPosition().y, width(), height() - ground->GetPosition().y);

    // 绘制小球
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPointF(ball->GetPosition().x, height() - ball->GetPosition().y), ball->GetFixtureList()->GetShape()->m_radius * 20, ball->GetFixtureList()->GetShape()->m_radius * 20);
}
