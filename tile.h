#ifndef TILE_H
#define TILE_H

#include <box2d/box2d.h>
#include "userData.h"
#include <QPainter>

//游戏世界中构成地图的方块
class tile
{
public:
    tile();
    tile(b2World *world, float x, float y, float hx, float hy);
    ~tile();
    void draw(QPainter *painter);

private:
    b2Body *body;
    b2BodyDef *bodyDef;
    b2FixtureDef *fixDef;
    b2BodyUserData *ud;
    b2PolygonShape *tileShape;
    //方块大小, 默认为1m*1m的方块
    float sizex = 0.5, sizey = 0.5;
};

#endif // TILE_H
