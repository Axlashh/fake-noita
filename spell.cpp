#include "wand.h"
#include "userData.h"
#include <QDebug>

spell::~spell() {
    delete ud;
    delete bodyDef;
    delete fixDef;
}

void spell::compute(wand *wd, mod m) {
    switch (this->type) {
    //普通投射物
    case projectile:
    case withTrigger:
        //计算投射物修正的数值
        this->speed *= m.sr;
        this->damage *= m.dr;
        break;

    //投射物修正
    case pmodifier:
        //修正乘以自身的倍率
        m.sr *= this->speedRate;
        m.dr *= this->damageRate;
        break;
    }
    //计算本法术所触发的法术
    this->spl = new spell*[this->drawNum];
    for (int i = 0; i < this->drawNum; i++) {
        spell *tp = wd->extract();
        if (tp == nullptr) break;
        this->spl[i] = tp;
    }
}

void spell::shoot(float x, float y, int degree, b2World *world) {
    if (this->type != pmodifier && this->type != multicast) {
        this->creatBody(x, y, world);
        this->setV(this->speed, degree);
    }

    if (this->type != withTrigger) {
        for (int i = 0; i < this->drawNum; i++) {
            this->spl[i]->shoot(x, y, degree, world);
        }
    }
}

int spell::getMana() {
    return this->manaCast;
}

int spell::getCastDelay() {
    return this->castDelay;
}

int spell::getRechargeTime() {
    return this->rechargeTime;
}

void spell::setV(int v, int degree) {
    int fixedDegree = degree + rand() % (2 * this->spread) - this->spread;
    float rad = fixedDegree * M_PI / 180.0f;
    float xv = v * cos(rad);
    float yv = v * sin(rad);
    b2Vec2 bv(xv, yv);
    this->body->SetLinearVelocity(bv);
}

void spell::creatBody(float x, float y, b2World *world) {
    bodyDef->position.Set(x, y);
    body = world->CreateBody(bodyDef);
    body->CreateFixture(fixDef);
}

//默认的法术绘图函数，什么都不画
void spell::draw(QPainter *painter, float PPM) {

}

void spell::copyTo(spell* t) {
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->ud = new b2BodyUserData();
    userData *uud = new userData();
    uud->p = (unsigned long long)t;
    uud->type = userDataType::spell;
    t->ud->pointer = (uintptr_t) uud;
    t->bodyDef->userData = *t->ud;
    t->fixDef = new b2FixtureDef(*this->fixDef);
    t->spl = new spell*[this->drawNum];
    for (int i = 0; i < drawNum; i++) t->spl[i] = this->spl[i];
}

void spell::update() {
    if (lifetime-- < 0)
        bomb();
}

//火花弹
sparkBolt::sparkBolt() {
    type = projectile;
    drawNum = 0;
    manaCast = 5;
    damage = 3;
    speed = 50;
    spread = 5;
    lifetime = 1200;
    castDelay = 3;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    r = 0.1;
    img = QImage("../23su/source/image/Spell_light_bullet.png");

    //初始化bodyDef
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    userData *uud = new userData();
    uud->p = (unsigned long long)this;
    uud->type = userDataType::spell;
    ud->pointer = (uintptr_t) uud;
    bodyDef->type = b2_dynamicBody;
    bodyDef->fixedRotation = false;
    bodyDef->userData = *ud;

    //初始化fixtureDef
    fixDef = new b2FixtureDef();
    b2CircleShape *cs = new b2CircleShape();
    cs->m_radius = r;
    fixDef->shape = cs;
    fixDef->density = 0.5f;
    fixDef->friction = 0;
}

sparkBolt* sparkBolt::copy() {
    sparkBolt* t = new sparkBolt(*this);
    this->copyTo(t);
    return t;
}

void sparkBolt::draw(QPainter *painter, float PPM) {
    auto vv = body->GetLinearVelocity();
    int degree = std::atan2(vv.y, vv.x) * (180.0 / M_PI);
    painter->save();
    painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
    painter->rotate(degree);
    painter->drawImage(QRectF(QPointF(-10.5f / 2.5f * r * PPM, -r * PPM), QPointF(r * PPM, r * PPM)), img);
    painter->restore();
}

//带触发的火花弹
sparkBoltt::sparkBoltt() {
    type = withTrigger;
    drawNum = 1;
    spl = new spell*[drawNum];
}

sparkBoltt::~sparkBoltt() {
    delete[] spl;
}

sparkBoltt* sparkBoltt::copy() {
    sparkBoltt* t = new sparkBoltt(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

energyOrb::energyOrb() {

}

energyOrb* energyOrb::copy() {
    energyOrb* t = new energyOrb(*this);
    this->copyTo(t);
    return t;
}

void energyOrb::draw(QPainter *painter, float PPM) {

}

energyOrbt::energyOrbt() {
}

energyOrbt* energyOrbt::copy() {
    energyOrbt* t = new energyOrbt(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

chain::chain() {

}

chain* chain::copy() {
    chain* t = new chain(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

void chain::draw(QPainter *painter, float PPM) {

}

doubleSpell::doubleSpell() {

}

doubleSpell* doubleSpell::copy() {
    doubleSpell* t = new doubleSpell(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

addMana::addMana() {

}

addMana* addMana::copy() {
    addMana* t = new addMana(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

speedUp::speedUp() {

}

speedUp* speedUp::copy() {
    speedUp* t = new speedUp(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}

damagePlus::damagePlus() {

}

damagePlus* damagePlus::copy() {
    damagePlus* t = new damagePlus(*this);
    t->bodyDef = new b2BodyDef(*this->bodyDef);
    t->fixDef = new b2FixtureDef(*this->fixDef);
    return t;
}
