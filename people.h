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
    void draw(QPainter *painter)	override;
    class::spell* getPak(int n);
    void swap(int wand1, int wand2, int spell1, int spell2);
    void hurt(int n)	override;
    float jump;
    float mana;
    bool onGround;
    int maxWand;
    int wandInHand;
    int backpackNum;

protected:
    void dead()	override;

private:
    wand **wnd;
    class::spell **backpack;

};

#endif // PEOPLE_H
