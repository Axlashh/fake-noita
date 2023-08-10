#include "people.h"

people::people() : character()
{
}

people::people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world) : character(bodyDef, fixDef, world)
{
    jump = 100;
    mana = 100;
    maxxSpeed = 3;
    maxySpeed = 4;
    wnd = new std::vector<wand>();
}

void people::moveRight() {
    body->SetLinearVelocity(b2Vec2(1.5, 0));
}

void people::moveLeft() {
    body->SetLinearVelocity(b2Vec2(-1.5, 0));
}
