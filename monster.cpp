#include "monster.h"
#include"QDebug"
zombie::zombie()
{
    blood = 50;
    isDead = false;
    onGround = false;
    damage = 50;
    bdelay = 180;
    delay  = 0;
    img = QImage("../23su/source/image/zombie.png").mirrored(false, true);
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    userData * uud =new userData();

    uud->p = (uintptr_t)this;
    uud->type = userDataType::monster;
    ud->pointer = (uintptr_t) uud;

    bodyDef->allowSleep = false;
    bodyDef->type = b2_dynamicBody;
    bodyDef->fixedRotation = true;
    bodyDef->userData = *ud;

    //定义fixtureDef
    b2PolygonShape *playerShape = new b2PolygonShape();
    playerShape->SetAsBox(0.5f, 1.0f);

    fixDef = new b2FixtureDef();
    fixDef->shape = playerShape;	//形状
    fixDef->friction = 0.5;		    //摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 30;			//密度
    fixDef->isSensor = false;       //传感器

    body = nullptr;
}


zombie::zombie(b2World *world, b2Vec2 pos) : zombie()
{
    bodyDef->position = pos;
    body = world->CreateBody(bodyDef);
    body->CreateFixture(this->fixDef);
}

zombie::~zombie()
{
    delete ud;
    delete bodyDef;
    delete fixDef;
}

void zombie::draw(QPainter *painter)
{
    painter->drawImage(QRectF(QPointF(body->GetPosition().x * PPM - this->getSize().x * PPM, body->GetPosition().y * PPM - this->getSize().y * PPM),
                             QPointF(body->GetPosition().x * PPM + this->getSize().x * PPM, body->GetPosition().y * PPM + this->getSize().y * PPM)), this->img);
}

void zombie::dead(){
    isDead = true;
}

void zombie::update(const b2Vec2 &&pos)
{
    delay++;
    if(delay == bdelay)
    {
       delay=0;
    }
    float x = pos.x;
    float y = pos.y;
    if(onGround&&delay==0)
    {
       if(x>body->GetPosition().x)
       {
           body->ApplyLinearImpulseToCenter(b2Vec2(200,300),true);

           //img = QImage("../23su/source/image/zombie.png").mirrored(true, true);
       }
       if(x<body->GetPosition().x)
           body->ApplyLinearImpulseToCenter(b2Vec2(-200,300),true);
    }
}
