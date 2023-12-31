#ifndef MONSTER_H
#define MONSTER_H
#include"character.h"
#include"userData.h"
#include "spell.h"


class zombie: public character
{
public:
    zombie();
    ~zombie()   override;
    zombie(b2World *world, b2Vec2 pos);
    void update(const b2Vec2 &pos)   override;
private:
    myRayCastCallback *rcc;
    const float impulse = 500;
};

class greenCutie : public character
{
public:
    greenCutie();
    ~greenCutie()	override;
    greenCutie(b2World *world, b2Vec2 pos);
    void update(const b2Vec2 &pos)	override;
private:
    myRayCastCallback *rcc;
    class::spell *spl;
};



#endif // MONSTER_H
