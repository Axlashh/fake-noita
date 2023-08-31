#ifndef CHARACTER_H
#define CHARACTER_H

#include <box2d/box2d.h>
#include <QPainter>
#include <string.h>
#include <QImage>
#include "userData.h"

class character {

public:
    virtual ~character() = 0;
    virtual void update();
    virtual void update(const b2Vec2 &pos);
    b2Vec2 getPos();
    b2Vec2 getSize();
    b2Vec2 getSpeed();
    virtual void draw(QPainter *painter);
    void hurt(int n);
    int getDamage();
    int getBlood();
    bool getDead();
    int getDelay();
    void setRcc();
    void setOnGround();
    float maxxSpeed;
    float maxySpeed;


protected:
    QImage img;
    QImage leftimg;
    QImage rightimg;
    virtual void dead();
    b2Body *body;
    b2BodyDef *bodyDef;
    b2FixtureDef *fixDef;
    b2BodyUserData *ud;
    userData *uud;
    float sizex;
    float sizey;
    int blood;
    int damage;
    bool isDead;
    int delay;
    int bdelay;
    bool onGround;
    bool isGround;
    bool rccSuc;
};


class myRayCastCallback: public b2RayCastCallback
{
public:
    myRayCastCallback(character *parent);
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                        const b2Vec2& normal, float fraction)   override;
    void setIsGround(character *p);
private:
    character *parent;
};
#endif // CHARACTER_H
