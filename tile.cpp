#include "tile.h"

tile::tile()
{
    img = QImage("../23su/source/image/basic_tile.png");
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
    b2PolygonShape *tileShape = new b2PolygonShape();
    tileShape->SetAsBox(size, size);
    fixDef = new b2FixtureDef();
    fixDef->shape = tileShape;	//形状
    fixDef->friction = 0;		//摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 0;			//密度
    fixDef->isSensor = false;

    body = nullptr;
}

tile::tile(b2World *world, float x, float y)  : tile()
{
    bodyDef->position.Set(x, y);
    body = world->CreateBody(bodyDef);
    body->CreateFixture(fixDef);
}

tile::~tile()
{
    delete ud;
    delete bodyDef;
    delete fixDef;
    body->GetWorld()->DestroyBody(body);
}

void tile::draw(QPainter *painter)
{
    painter->save();
    painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
    painter->drawImage(QRectF(QPointF(-size * PPM, -size * PPM), QPointF(size * PPM, size * PPM)), img);
    painter->restore();
}
