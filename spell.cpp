#include "wand.h"
#include "userData.h"
#include <QDebug>

spell::~spell() {
    if (bodyDef != nullptr)
        delete bodyDef;
    if (fixDef != nullptr)
        delete fixDef;
    if (body != nullptr)
        body->GetWorld()->DestroyBody(body);
    if (ud != nullptr)
        delete ud;
    if (spl != nullptr)
        delete[] spl;
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
    for (int i = 0; i < this->drawNum; i++) {
        spell *tp = wd->extract(m, true);
        this->spl[i] = tp;
        if (tp == nullptr) break;
    }
}

void spell::shoot(float x, float y, int degree, b2World *world) {
    if (this->type != pmodifier && this->type != multicast) {
        this->creatBody(x, y, world, degree);
        this->setV(this->speed, degree);
    }

    if (this->type != withTrigger) {
        for (int i = 0; i < this->drawNum; i++) {
            if (this->spl[i] == nullptr) break;
            this->spl[i]->shoot(x, y, degree, world);
        }
    }
}

QString spell::getName() {
    return name;
}

QString spell::getExtraInfo() {
    return extraInfo;
}

int spell::getType() {
    return type;
}

int spell::getManaCast() {
    return manaCast;
}

int spell::getDamage() {
    return damage;
}

int spell::getSpeed() {
    return speed;
}

int spell::getSpread() {
    return spread;
}

int spell::getLifetime() {
    return lifetime;
}

int spell::getDelay() {
    return delay;
}

int spell::getRechargeTime() {
    return rechargeTime;
}

float spell::getSpeedRate() {
    return speedRate;
}

float spell::getDamageRate() {
    return damageRate;
}

float spell::getR() {
    return r;
}

void spell::setV(int v, int degree) {
    int fixedDegree = degree + rand() % (2 * this->spread) - this->spread;
    float rad = fixedDegree * M_PI / 180.0f;
    float xv = v * cos(rad);
    float yv = v * sin(rad);
    b2Vec2 bv(xv, yv);
    this->body->SetLinearVelocity(bv);
}

void spell::creatBody(float x, float y, b2World *world, int deg) {
    bodyDef->position.Set(x + cos(deg / 180.0f * M_PI) * r, y + sin(deg / 180.0f * M_PI) * r);
    body = world->CreateBody(bodyDef);
    body->CreateFixture(fixDef);
}

QImage* spell::getimg() {
    return &img;
}

bool spell::dead() {
    return isDead;
}

bool spell::safe() {
    return isSafe;
}

void spell::draw(QPainter *painter) {
    if (isBomb) {
        if (bombTime-- < 0) {
            isDead = true;
            return;
        }
        if (!triggerShooted) {
            for (int i = 0; i < drawNum; i++) {
                if (spl[i] == nullptr) break;
                spl[i]->shoot(triggerPos.x, triggerPos.y, triggerDeg, body->GetWorld());
            }
            triggerShooted = true;
        }
        painter->save();
        painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
        painter->drawImage(bombRec, bombImg);
        painter->restore();
        return;
    }
    if (lifetime-- < 0) {
        bomb();
        return;
    }
    auto vv = body->GetLinearVelocity();
    int degree = std::atan2(vv.y, vv.x) * (180.0 / M_PI);
    painter->save();
    painter->translate(body->GetPosition().x * PPM, body->GetPosition().y * PPM);
    painter->rotate(degree);
    painter->drawImage(shootRec, shootImg);
    painter->restore();

}

class::spell* spell::copy() {return nullptr;}

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

void spell::bomb() {
    isBomb = true;
    if (type == withTrigger) {
        b2Vec2 v = body->GetLinearVelocity();
        triggerDeg = std::atan2(v.y, v.x) * 180.0 / M_PI;
        triggerPos = body->GetPosition();
    }
    if (body != nullptr){
        body->SetAwake(false);
    }
}

void spell::bomb(int deg) {
    isBomb = true;
    if (type == withTrigger) {
        b2Vec2 v = body->GetLinearVelocity();
        triggerDeg = std::atan2(v.y, v.x) * 180.0 / M_PI;
        triggerDeg = 2 * deg - triggerDeg + 180;
        triggerPos = body->GetPosition();
        int tv = sqrt(v.x * v.x + v.y * v.y);
        triggerPos.x += 0.01 * tv * cos(triggerDeg * M_PI / 180);
        triggerPos.y += 0.01 * tv * sin(triggerDeg * M_PI / 180);
    }
    if (body != nullptr){
        b2Fixture* tf = body->GetFixtureList();
        b2Filter tfi = tf->GetFilterData();
        tfi.maskBits = 0x0000;
        tf->SetFilterData(tfi);
        body->SetAwake(false);
    }
}

//火花弹
sparkBolt::sparkBolt() {
    name = "火花弹";
    extraInfo = "威力小，速度快的普通魔法弹";
    type = projectile;
    drawNum = 0;
    manaCast = 10;
    damage = 3;
    speed = 50;
    spread = 5;
    lifetime = 1200;
    delay = 3;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    body = nullptr;
    r = 0.1;
    img = QImage("../23su/source/image/Spell_light_bullet.png");
    shootImg = QImage("../23su/source/image/Spell_light_bullet.png");
    bombImg = QImage("../23su/source/image/slbbb.png");
    isBomb = false;
    bombTime = 5;
    isDead = false;
    isSafe = false;
    triggerShooted = true;
    shootRec = QRectF(QPointF(-10.5f / 2.5f * r * PPM, -r * PPM), QPointF(r * PPM, r * PPM));
    bombRec = QRectF(QPointF(-3 * r * PPM, -3 * r * PPM), QPointF(3 * r * PPM, 3 * r * PPM));

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
    fixDef->filter.categoryBits = 0x0001;
    fixDef->filter.maskBits = 0xfffe;
}

sparkBolt* sparkBolt::copy() {
    sparkBolt* t = new sparkBolt(*this);
    this->copyTo(t);
    return t;
}

//带定时的火花弹
sparkBoltt::sparkBoltt(){
    name = "带定时的火花弹";
    extraInfo = "在定时结束或爆炸后施放另一法术的火花弹";
    img = QImage("../23su/source/image/Spell_light_bullet_timer.png");
    lifetime = 10;
    type = withTrigger;
    triggerShooted = false;
    drawNum = 1;
    spl = new spell*[drawNum];
}

sparkBoltt* sparkBoltt::copy() {
    sparkBoltt* t = new sparkBoltt(*this);
    this->copyTo(t);
    return t;
}

energyOrb::energyOrb() {
    name = "能量球";
    extraInfo = "缓慢而强大的能量球体";
    type = projectile;
    drawNum = 0;
    manaCast = 20;
    damage = 18;
    speed = 15;
    spread = 10;
    lifetime = 1200;
    delay = 8;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    body = nullptr;
    r = 0.8;
    img = QImage("../23su/source/image/Spell_slow_bullet.png");
    shootImg = QImage("../23su/source/image/Spell_slow_bullet_shoot.png");
    bombImg = QImage("../23su/source/image/slbbb.png");
    isBomb = false;
    bombTime = 5;
    isDead = false;
    isSafe = false;
    triggerShooted = true;
    shootRec = QRectF(QPointF(-r * PPM, -r * PPM), QPointF(r * PPM, r * PPM));
    bombRec = QRectF(QPointF(-1.5 * r * PPM, -1.5  * r * PPM), QPointF(1.5  * r * PPM, 1.5 * r * PPM));

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
    bodyDef->gravityScale = 0;

    //初始化fixtureDef
    fixDef = new b2FixtureDef();
    b2CircleShape *cs = new b2CircleShape();
    cs->m_radius = r;
    fixDef->shape = cs;
    fixDef->density = 0.5f;
    fixDef->friction = 0;
    fixDef->filter.categoryBits = 0x0001;
    fixDef->filter.maskBits = 0xfffe;
}

energyOrb* energyOrb::copy() {
    energyOrb* t = new energyOrb(*this);
    this->copyTo(t);
    return t;
}

energyOrbt::energyOrbt() {
    name = "带定时的能量球";
    extraInfo = "在定时结束或爆炸后施放另一法术的能量球";
    img = QImage("../23su/source/image/Spell_slow_bullet_timer.png");
    lifetime = 30;
    type = withTrigger;
    triggerShooted = false;
    drawNum = 1;
    spl = new spell*[drawNum];
}

energyOrbt* energyOrbt::copy() {
    energyOrbt* t = new energyOrbt(*this);
    this->copyTo(t);
    return t;
}

chain::chain() {
    name = "链锯";
    extraInfo = "看起来更应该叫小火花\n能清除本轮法术释放的施放延迟！";
    type = projectile;
    drawNum = 0;
    manaCast = 5;
    damage = 10;
    speed = 0;
    spread = 5;
    lifetime = 3;
    delay = -1000;
    rechargeTime = -10;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    body = nullptr;
    r = 0.3;
    imgs = new QImage[3];
    imgs[0] = QImage("../23su/source/image/chain0.png");
    imgs[1] = QImage("../23su/source/image/chain1.png");
    imgs[2] = QImage("../23su/source/image/chain2.png");
    img = QImage("../23su/source/image/Spell_chainsaw.png");
    bombImg = imgs[0];
    isBomb = false;
    bombTime = 5;
    isDead = false;
    isSafe = true;
    triggerShooted = true;
    shootRec = QRectF(QPointF(-2 * r * PPM, -2 * r * PPM), QPointF(2 * r * PPM, 2 * r * PPM));
    bombRec = QRectF(QPointF(-2 * r * PPM, -2 * r * PPM), QPointF(2 * r * PPM, 2 * r * PPM));

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
    bodyDef->gravityScale = 0;

    //初始化fixtureDef
    fixDef = new b2FixtureDef();
    b2CircleShape *cs = new b2CircleShape();
    cs->m_radius = r;
    fixDef->shape = cs;
    fixDef->density = 0.5f;
    fixDef->friction = 0;
}

chain* chain::copy() {
    chain* t = new chain(*this);
    this->copyTo(t);
    return t;
}

void chain::draw(QPainter *painter) {
    int k = rand() % 3;
    shootImg = imgs[k];
    spell::draw(painter);
}

doubleSpell::doubleSpell() {
    name = "双重释放";
    extraInfo = "同时释放接下来的两个法术";
    type = multicast;
    drawNum = 2;
    manaCast = 0;
    delay = 0;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    img = QImage("../23su/source/image/Spell_burst.png");
}

doubleSpell* doubleSpell::copy() {
    doubleSpell* t = new doubleSpell(*this);
    t->spl = new spell*[drawNum];
    return t;
}

addMana::addMana() {
    name = "增加魔力";
    extraInfo = "释放后能增加30点魔力，朴实无华";
    type = pmodifier;
    drawNum = 1;
    manaCast = -30;
    delay = 10;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    img = QImage("../23su/source/image/Spell_mana.png");
}

addMana* addMana::copy() {
    addMana* t = new addMana(*this);
    t->spl = new spell*[drawNum];
    return t;
}

speedUp::speedUp() {
    name = "加速";
    extraInfo = "嗖嗖嗖！";
    type = pmodifier;
    drawNum = 1;
    manaCast = 5;
    delay = 0;
    rechargeTime = 0;
    speedRate = 2.0;
    damageRate = 1;
    spl = nullptr;
    img = QImage("../23su/source/image/Spell_speed.png");
}

speedUp* speedUp::copy() {
    speedUp* t = new speedUp(*this);
    t->spl = new spell*[drawNum];
    return t;
}

damagePlus::damagePlus() {
    name = "伤害增强";
    extraInfo = "杀杀杀！";
    type = pmodifier;
    drawNum = 1;
    manaCast = 5;
    delay = 5;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1.1;
    spl = nullptr;
    img = QImage("../23su/source/image/Spell_damage.png");
}

damagePlus* damagePlus::copy() {
    damagePlus* t = new damagePlus(*this);
    t->spl = new spell*[drawNum];
    return t;
}

slimeBall::slimeBall() {
    name = "粘液球 怪物专属";
    extraInfo = "湿漉漉的";
    type = projectile;
    drawNum = 0;
    manaCast = 10;
    damage = 10;
    speed = 20;
    spread = 1;
    lifetime = 1200;
    delay = 3;
    rechargeTime = 0;
    speedRate = 1;
    damageRate = 1;
    spl = nullptr;
    body = nullptr;
    r = 0.3;
    img = QImage("../23su/source/image/Spell_slimeball.png");
    shootImg = QImage("../23su/source/image/Spell_slimeball.png");
    bombImg = QImage("../23su/source/image/slbbb.png");
    isBomb = false;
    bombTime = 5;
    isDead = false;
    isSafe = false;
    triggerShooted = true;
    shootRec = QRectF(QPointF(-10.5f / 2.5f * r * PPM, -r * PPM), QPointF(r * PPM, r * PPM));
    bombRec = QRectF(QPointF(-1.5 * r * PPM, -1.5 * r * PPM), QPointF(1.5 * r * PPM, 1.5 * r * PPM));

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
    fixDef->filter.categoryBits = 0x0001;
    fixDef->filter.maskBits = 0xfffe;
}

slimeBall* slimeBall::copy() {
    slimeBall* t = new slimeBall(*this);
    this->copyTo(t);
    return t;
}
