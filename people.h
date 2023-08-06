#ifndef PEOPLE_H
#define PEOPLE_H

#include "character.h"

class people : public character
{
public:
    people();
    people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world, bool isPlayer = false);
    void moveRight() override;
    void moveLeft() override;
    float jump;
    float mana;
    bool onGround;
};

#endif // PEOPLE_H
