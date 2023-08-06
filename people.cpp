#include "people.h"

people::people() : character()
{
    maxxSpeed = 3;
}

people::people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world, bool isPlayer) : character(bodyDef, fixDef, world)
{
    jump = 100;
    mana = 100;
    maxxSpeed = 3;
    maxySpeed = 4;



}

void people::moveRight() {
    body->SetLinearVelocity(b2Vec2(1.5, 0));
}

void people::moveLeft() {
    body->SetLinearVelocity(b2Vec2(-1.5, 0));
}
