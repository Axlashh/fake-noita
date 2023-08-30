#include "tile.h"

tile::tile()
{
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    userData *uud = new userData();
    uud->p = (unsigned long long) this;
    uud->type = userDataType::ground;
    ud->pointer = (uintptr_t) uud;

    bodyDef->allowSleep = true;
    bodyDef->type = b2_staticBody;
    bodyDef->fixedRotation = true;
    bodyDef->userData = *ud;

    //定义fixtureDef
    tileShape = new b2PolygonShape();

    fixDef = new b2FixtureDef();
    fixDef->friction = 1;		//摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 0;			//密度
    fixDef->isSensor = false;

    body = nullptr;
}

tile::tile(b2World *world, float x, float y, float hx, float hy)  : tile()
{
    sizex = hx, sizey = hy;
    tileShape->SetAsBox(sizex, sizey);
    fixDef->shape = tileShape;
    bodyDef->position.Set(x, y);
    body = world->CreateBody(bodyDef);
    body->CreateFixture(fixDef);
}

tile::~tile()
{
    delete ud;
    delete bodyDef;
    delete fixDef;
    delete tileShape;
    body->GetWorld()->DestroyBody(body);
}

void tile::draw(QPainter *painter)
{
    painter->save();
    painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
    painter->setPen(QPen(QColor(0xb6, 0x32, 0x31), 2));
    painter->fillRect(QRectF(QPointF(-sizex * PPM, -sizey * PPM), QPointF(sizex * PPM, sizey * PPM)), QColor(0xa1, 0xa3, 0xb4));
    painter->drawRect(QRectF(QPointF(-sizex * PPM, -sizey * PPM), QPointF(sizex * PPM, sizey * PPM)));
    painter->restore();
}
