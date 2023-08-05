#ifndef PEOPLE_H
#define PEOPLE_H

#include "character.h"

class people : public character
{
public:
    people();
    people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world);
    void moveRight() override;
    void moveLeft() override;
};

#endif // PEOPLE_H
