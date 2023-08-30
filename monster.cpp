#include "monster.h"
#include"QDebug"
zombie::zombie()
{
    blood = 50;
    isDead = false;
    onGround = false;
    isGround = false;
    damage = 50;
    bdelay = 120;
    delay  = 0;
    img = QImage("../23su/source/image/zombie.png").mirrored(false, true);
    leftimg=QImage("../23su/source/image/zombie.png").mirrored(true, true);
    rightimg=QImage("../23su/source/image/zombie.png").mirrored(false, true);
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
    fixDef->density = 20;			//密度
    fixDef->isSensor = false;       //传感器

    body = nullptr;
    rcc = new myRayCastCallback(this);
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
    float radian = std::atan2(y - body->GetPosition().y , x - body->GetPosition().x );
    int degree = radian * (180.0 / M_PI);
    float sn=sin(radian);
    float cs=cos(radian);
    body->GetWorld()->RayCast(rcc,pos,body->GetPosition());
    if(onGround && delay==0 && !isGround)
    {
       if((x-body->GetPosition().x)*(x-body->GetPosition().x)+(y-body->GetPosition().y)*(y-body->GetPosition().y)<1000)
       {
           onGround = false;
           if(x>body->GetPosition().x)
           {
               img = leftimg;
               body->ApplyLinearImpulseToCenter(b2Vec2(400*cs,400*sn),true);
           }
           if(x<body->GetPosition().x)
           {
               img = rightimg;
               body->ApplyLinearImpulseToCenter(b2Vec2(400*cs,400*sn),true);
           }
       }
    }
    isGround = false;
}

