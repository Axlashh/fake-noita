#ifndef CHARACTER_H
#define CHARACTER_H

#include <box2d/box2d.h>
#include <string.h>

class character {

public:
    character();
    character(b2BodyDef *bodyDef,b2FixtureDef *fixDef, b2World *world);
    void setBodyDef(b2BodyDef *bodyDef, b2World *world);
    void setFixtrue(b2FixtureDef *fixDef);
    void setBlood();
    b2Vec2 getPos();
    b2Vec2 getSize();
    b2Vec2 getSpeed();
    void addForce(b2Vec2 f);
    void setSpeed(b2Vec2 f);
    void setSpeed(float x, float y);
    virtual void moveLeft();
    virtual void moveRight();
    float maxxSpeed;
    float maxySpeed;

protected:
    b2Body *body;
    float sizex;
    float sizey;
    int blood;
};
#endif // CHARACTER_H
