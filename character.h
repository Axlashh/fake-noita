#ifndef CHARACTER_H
#define CHARACTER_H

#include <box2d/box2d.h>
#include <QPainter>
#include <string.h>
#include <QImage>
#include "userData.h"

class character {

public:
    character();
    virtual ~character() = 0;
    character(b2World *world, b2Vec2 pos);
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
    virtual void draw(QPainter *painter) = 0;
    virtual void hurt(int n) = 0;
    int getDamage();
    int getBlood();
    float maxxSpeed;
    float maxySpeed;
    QImage img;


protected:
    virtual void dead() = 0;
    b2Body *body;
    b2BodyDef *bodyDef;
    b2FixtureDef *fixDef;
    userData *ud;
    float sizex;
    float sizey;
    int blood;
    int damage;
};
#endif // CHARACTER_H
