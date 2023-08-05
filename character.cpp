#include "character.h"

character::character() {
    body = nullptr;
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

b2Vec2 character::getPos() {
    return body->GetPosition();
}

b2Vec2 character::getSize() {
    b2Vec2 t = body->GetFixtureList()->GetAABB(0).GetExtents();
    return b2Vec2(t.x * 2, t.y * 2);
}

void character::moveLeft() {

}

void character::moveRight() {

}
