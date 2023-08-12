#ifndef PEOPLE_H
#define PEOPLE_H

#include "character.h"
#include "wand.h"

class people : public character
{
public:
    people();
    people(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world);
    void moveRight() override;
    void moveLeft() override;
    wand* getWand(int n);
    void addWand(wand *w, int n);
    float jump;
    float mana;
    bool onGround;
    int maxWand;
    int wandInHand;

private:
    wand **wnd;

};

#endif // PEOPLE_H
