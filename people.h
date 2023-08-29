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
    wand* getWand(int n);
    void addWand(wand *w, int n);
    bool addSpell(class::spell *spl);
    void draw(QPainter *painter)	override;
    class::spell* getPak(int n);
    void swap(int wand1, int wand2, int spell1, int spell2);
    void move(bool isPressed[]);
    int getMaxWand();
    int getJump();

protected:
    void dead()	override;

private:
    float jump;
    int maxWand;
    int backpackNum;
    wand **wnd;
    class::spell **backpack;

};

#endif // PEOPLE_H
