#include "people.h"

people::people() : character()
{
}

people::people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world) : character(bodyDef, fixDef, world)
{
    img = QImage("../23su/source/image/player.jpg").mirrored(false, true);
    jump = 100;
    mana = 100;
    maxxSpeed = 3;
    maxySpeed = 4;
    maxWand = 2;
    wandInHand = 0;
    wnd = new wand*[maxWand];
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
