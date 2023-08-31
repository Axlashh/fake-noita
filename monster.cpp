#include "monster.h"
#include"QDebug"
#define bdata 450
zombie::zombie()
{
    blood = 50;
    isDead = false;
    isGround=false;
    onGround = false;
    rccSuc=false;
    damage = 50;
    bdelay = 120;
    delay  = 0;
    img = QImage("../23su/source/image/zombie.png").mirrored(false, true);
    leftimg=QImage("../23su/source/image/zombie.png").mirrored(true, true);
    rightimg=QImage("../23su/source/image/zombie.png").mirrored(false, true);
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    uud =new userData();

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
    fixDef->filter.categoryBits = 0x0002;

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
    delete uud;
    delete bodyDef;
    delete fixDef;
    delete rcc;
}

void zombie::update(const b2Vec2 &pos)
{
    delay++;
    if(delay == bdelay)
    {
       delay=0;
    }
    float x = pos.x;
    float y = pos.y;
    float radian = std::atan2(y - body->GetPosition().y , x - body->GetPosition().x );
    float sn=sin(radian);
    float cs=cos(radian);
    onGround = false;
    isGround = false;

    //检测僵尸与人之间是否有阻挡
    body->GetWorld()->RayCast(rcc,pos,body->GetPosition());
    if (rccSuc) {
       isGround = true;
       rccSuc = false;
    }
    //检测是否在地面上
    b2Vec2 pos1(body->GetPosition().x,body->GetPosition().y-1.1);
    body->GetWorld()->RayCast(rcc,body->GetPosition(),pos1);

    if (rccSuc) {
       onGround = true;
       rccSuc = false;
    }

    if(onGround && delay==0 && !isGround)
    {
       if((x-body->GetPosition().x)*(x-body->GetPosition().x)+(y-body->GetPosition().y)*(y-body->GetPosition().y)<1000)
       {
           if(x>body->GetPosition().x)
           {
               img = leftimg;
               body->ApplyLinearImpulseToCenter(b2Vec2(bdata*cs,bdata*sn),true);
           }
           if(x<body->GetPosition().x)
           {
               img = rightimg;
               body->ApplyLinearImpulseToCenter(b2Vec2(bdata*cs,bdata*sn),true);
           }
       }
    }
    if(onGround && isGround && delay==0)
    {
       int ra1=rand() % 4+1 ;
       int ra2=rand() % 2 ;
       int ra3=ra1;
       if(ra2==0)
       {
           ra1=-ra1;
           img=rightimg;
       }
       else
          img=leftimg;
       body->ApplyLinearImpulseToCenter(b2Vec2(70*ra1,70*ra3),true);
       qDebug()<<ra1;
    }
}

greenCutie::greenCutie() {
    blood = 30;
    isDead = false;
    onGround = false;
    isGround = false;
    damage = 20;
    bdelay = 120;
    delay  = 0;
    leftimg=QImage("../23su/source/image/floatMonster.png").mirrored(false, true);
    rightimg=QImage("../23su/source/image/floatMonster.png").mirrored(true, true);
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    uud =new userData();

    uud->p = (uintptr_t)this;
    uud->type = userDataType::monster;
    ud->pointer = (uintptr_t) uud;

    bodyDef->allowSleep = false;
    bodyDef->type = b2_dynamicBody;
    bodyDef->fixedRotation = true;
    bodyDef->userData = *ud;
    bodyDef->gravityScale = 0;

    //定义fixtureDef
    b2PolygonShape *playerShape = new b2PolygonShape();
    playerShape->SetAsBox(0.5f, 0.5f);

    fixDef = new b2FixtureDef();
    fixDef->shape = playerShape;	//形状
    fixDef->isSensor = false;       //传感器
    fixDef->filter.categoryBits = 0x0002;

    body = nullptr;
    rcc = new myRayCastCallback(this);
    spl = new slimeBall();
}

greenCutie::greenCutie(b2World *world, b2Vec2 pos) : greenCutie(){
    bodyDef->position = pos;
    body = world->CreateBody(bodyDef);
    body->CreateFixture(this->fixDef);
}

greenCutie::~greenCutie() {
    delete ud;
    delete uud;
    delete bodyDef;
    delete fixDef;
    delete rcc;
}

void greenCutie::update(const b2Vec2 &pos) {
    delay++;
    if(delay == bdelay)
    {
       delay=0;
    }
    float x = pos.x;
    float y = pos.y;
    float bx = body->GetPosition().x;
    float by = body->GetPosition().y;
    float radian = std::atan2(y - by , x - bx );
    float sn=sin(radian);
    float cs=cos(radian);
    isGround = false;

    //检测与人之间是否有阻挡
    body->GetWorld()->RayCast(rcc,pos,body->GetPosition());
    if (rccSuc) {
       isGround = true;
       rccSuc = false;
    }

    img = cs > 0 ? leftimg : rightimg;

    //设置移动速度
    if (isGround) {
       body->SetLinearVelocity(b2Vec2((cs > 0 ? 1 : -1) * 1, 0));
    } else if ((x-body->GetPosition().x)*(x-body->GetPosition().x)+(y-body->GetPosition().y)*(y-body->GetPosition().y) > 10) {
       body->SetLinearVelocity(b2Vec2(cs, sn));
    }

    if (!isGround && delay == 0) {
       spl->copy()->shoot(bx + cs, by + sn, radian / M_PI * 180.0, body->GetWorld());
    }
}
