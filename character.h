#ifndef CHARACTER_H
#define CHARACTER_H

#include <box2d/box2d.h>

class character {

public:
    character();
    character(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world);
    const b2Vec2 GetPosition();
    void setBodyDef(b2BodyDef *bodyDef, b2World *world);
    void setFixtrue(b2FixtureDef *fixDef);
    b2Vec2 getPos();
    b2Vec2 getSize();
    virtual void moveLeft();
    virtual void moveRight();

private:
    b2Body *body;
    float sizex;
    float sizey;
    int blood;

};
#endif // CHARACTER_H
