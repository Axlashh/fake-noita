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
    void update()   override;
    void move(b2Vec2 pos)	override;

private:
    int delay;
    void dead() override;
};





#endif // MONSTER_H
