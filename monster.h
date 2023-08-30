#ifndef MONSTER_H
#define MONSTER_H
#include"character.h"
#include"userData.h"


class zombie: public character
{
public:
    zombie();
    ~zombie()   override;
    zombie(b2World *world, b2Vec2 pos);
    void draw(QPainter *painter)  override;
    void update(const b2Vec2 &&pos)   override;
private:
    void dead() override;
    myRayCastCallback * rcc;
};





#endif // MONSTER_H
