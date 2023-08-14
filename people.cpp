#include "people.h"

people::people()
{
    //定义bodyDef
    bodyDef = new b2BodyDef();
    b2BodyUserData t;
    ud = new userData();
    ud->p = (uintptr_t)this;
    ud->type = userDataType::player;
    t.pointer = (uintptr_t) ud;

    bodyDef->allowSleep = false;
    bodyDef->type = b2_dynamicBody;
    bodyDef->fixedRotation = true;
    bodyDef->userData = t;

    //定义fixtureDef
    b2PolygonShape *playerShape = new b2PolygonShape();
    playerShape->SetAsBox(0.5f, 1.0f);
    fixDef = new b2FixtureDef();
    fixDef->shape = playerShape;	//形状
    fixDef->friction = 0.5;		//摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 30;			//密度
    fixDef->isSensor = false;

    body = nullptr;
    blood = 100;
    jump = 100;
    mana = 100;
    maxxSpeed = 3;
    maxySpeed = 4;
    maxWand = 2;
    wandInHand = 0;
    wnd = new wand*[maxWand];
    for (int i = 0; i < maxWand; i++) {
        wnd[i] = nullptr;
    }
    img = QImage("../23su/source/image/player.jpg").mirrored(false, true);
}

people::people(b2World *world, b2Vec2 pos) : people()
{
    bodyDef->position = pos;
    body = world->CreateBody(bodyDef);
    body->CreateFixture(this->fixDef);
}

people::~people() {
    delete ud;
    delete bodyDef;
    delete fixDef;
    delete wnd;
}

void people::moveRight() {
    body->SetLinearVelocity(b2Vec2(1.5, 0));
}

void people::moveLeft() {
    body->SetLinearVelocity(b2Vec2(-1.5, 0));
}

void people::addWand(wand *w, int n) {
    if (n >= maxWand || n < 0) return;
    this->wnd[n] = w;
}

wand* people::getWand(int n) {
    if (n >= maxWand || n < 0) return nullptr;
    return wnd[n];
}

void people::draw(QPainter *painter, float PPM) {
    painter->drawImage(QRectF(QPointF(body->GetPosition().x * PPM - this->getSize().x * PPM, body->GetPosition().y * PPM - this->getSize().y * PPM),
                             QPointF(body->GetPosition().x * PPM + this->getSize().x * PPM, body->GetPosition().y * PPM + this->getSize().y * PPM)), this->img);
}
