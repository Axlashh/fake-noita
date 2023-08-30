#include "character.h"

character::character() {
    body = nullptr;
    blood = 100;
}

character::character(b2World *world, b2Vec2 pos) : character() {
}

character::~character() {}

void character::update() {}
void character::update(const b2Vec2 &&pos){}
void character::draw(QPainter *painter) {}


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

void character::setOnGround() {
    onGround = true;
}

void character::setIsGround() {
    isGround = true;
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
        setIsGround(parent);
        fraction=0;
    }
    else
        fraction=1;
    return fraction;
};

void myRayCastCallback::setIsGround(character *p) {
    p->setIsGround();
}
