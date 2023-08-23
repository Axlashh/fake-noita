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
    b2Vec2 getPos();
    b2Vec2 getSize();
    b2Vec2 getSpeed();
    virtual void draw(QPainter *painter) = 0;
    void hurt(int n);
    int getDamage();
    int getBlood();
    virtual void move(b2Vec2 pos) = 0;
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
