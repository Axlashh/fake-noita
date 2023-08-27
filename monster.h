#ifndef MONSTER_H
#define MONSTER_H
#include"character.h"
#include"userData.h"

class zombie:public character
{
public:
    zombie();
    ~zombie();
    zombie(b2World *world,b2Vec2 pos);
    void draw(QPainter * painter);
};





#endif // MONSTER_H
