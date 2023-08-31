#include "character.h"

character::~character() {}

void character::update() {}
void character::update(const b2Vec2 &pos){}

//得到物体的质心坐标
b2Vec2 character::getPos() {
    return body->GetPosition();
}

//得到物体包围框的半长，半宽
b2Vec2 character::getSize() {
    b2Vec2 t = body->GetFixtureList()->GetAABB(0).GetExtents();
    return b2Vec2(t.x, t.y);
}

b2Vec2 character::getSpeed() {
    return body->GetLinearVelocity();
}

void character::draw(QPainter *painter) {
    painter->save();
    painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
    painter->drawImage(QRectF(QPointF(-this->getSize().x * PPM, -this->getSize().y * PPM),
                             QPointF(this->getSize().x * PPM, this->getSize().y * PPM)), img);
    painter->restore();
}

void character::hurt(int n) {
    blood -= n;
    if (blood <= 0) {
        dead();
    }
}

int character::getDamage() {
    return damage;
}

int character::getBlood() {
    return blood;
}

bool character::getDead() {
    return isDead;
}

int character::getDelay() {
    return delay;
}

void character::setRcc()
{
    rccSuc = true;
}

void character::setOnGround() {
    onGround = true;
}

void character::dead() {
    isDead = true;
}

myRayCastCallback::myRayCastCallback(character *parent) :
    parent(parent)
{}

float myRayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                    const b2Vec2& normal, float fraction)
{
    userData *ud = reinterpret_cast<userData*>(fixture->GetBody()->GetUserData().pointer);
    if(ud->type == userDataType::ground)
    {
        parent->setRcc();
        fraction=0;
    }
    else
        fraction=1;
    return fraction;
};
