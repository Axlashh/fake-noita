#ifndef MONSTER_H
#define MONSTER_H
#include"character.h"
#include"userData.h"

class zombie:public character
{
public:
    zombie();
    ~zombie()   override;
    zombie(b2World *world,b2Vec2 pos);
    void draw(QPainter * painter)  override;
    void update()   override;
private:
    int delay;

};





#endif // MONSTER_H
