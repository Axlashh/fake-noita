#include "monster.h"

zombie::zombie()
{
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
    fixDef->friction = 1;		    //摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 50;			//密度
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
void zombie::move(b2Vec2 pos) {
}
void zombie::dead(){}

void zombie::update()
{

}
