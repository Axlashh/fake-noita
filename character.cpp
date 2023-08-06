#include "character.h"

character::character() {
    body = nullptr;
    blood = 100;
}

character::character(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world) : character() {
    setBodyDef(bodyDef, world);
    setFixtrue(fixDef);
}

void character::setBodyDef(b2BodyDef *bodyDef, b2World *world) {
    body = world->CreateBody(bodyDef);
}

void character::setFixtrue(b2FixtureDef *fixDef) {
    body->CreateFixture(fixDef);
}

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

void character::addForce(b2Vec2 f) {
    body->ApplyForceToCenter(f, true);
}

void character::setSpeed(b2Vec2 f) {
    body->SetLinearVelocity(f);
}

void character::setSpeed(float x, float y) {
    b2Vec2 t(x, y);
    body->SetLinearVelocity(t);
}

void character::moveLeft() {

}

void character::moveRight() {

}
