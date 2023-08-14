#ifndef PEOPLE_H
#define PEOPLE_H

#include "character.h"
#include "wand.h"
#include "userData.h"

class people : public character
{
public:
    people();
    ~people()	override;
    people(b2World *world, b2Vec2 pos);
    void moveRight() override;
    void moveLeft() override;
    wand* getWand(int n);
    void addWand(wand *w, int n);
    void draw(QPainter *painter, float PPM)	override;
    float jump;
    float mana;
    bool onGround;
    int maxWand;
    int wandInHand;

private:
    wand **wnd;

};

#endif // PEOPLE_H
