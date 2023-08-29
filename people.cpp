#include "people.h"
#include <QDebug>

people::people()
{
    //定义bodyDef
    bodyDef = new b2BodyDef();
    ud = new b2BodyUserData();
    userData *uud = new userData();
    uud->p = (uintptr_t)this;
    uud->type = userDataType::player;
    ud->pointer = (uintptr_t) uud;

    bodyDef->allowSleep = false;
    bodyDef->type = b2_dynamicBody;
    bodyDef->fixedRotation = true;
    bodyDef->userData = *ud;

    //定义fixtureDef
    b2PolygonShape *playerShape = new b2PolygonShape();
    playerShape->SetAsBox(0.5f, 1.0f);
    fixDef = new b2FixtureDef();
    fixDef->shape = playerShape;	//形状
    fixDef->friction = 0.5;		//摩擦系数
    fixDef->restitution = 0; 		//弹性
    fixDef->density = 30;			//密度
    fixDef->isSensor = false;

    body = nullptr;
    blood = 100;
    jump = 100;
    maxxSpeed = 3;
    maxySpeed = 4;
    maxWand = 2;
    wnd = new wand*[maxWand];
    for (int i = 0; i < maxWand; i++) {
        wnd[i] = nullptr;
    }
    img = QImage("../23su/source/image/player.png").mirrored(false, true);
    backpackNum = 11;
    backpack = new class::spell*[backpackNum];
    for (int i = 0; i < backpackNum; i++)
        backpack[i] = nullptr;
}

people::people(b2World *world, b2Vec2 pos) : people()
{
    bodyDef->position = pos;
    body = world->CreateBody(bodyDef);
    body->CreateFixture(this->fixDef);
}

people::~people() {
    delete ud;
    delete bodyDef;
    delete fixDef;
    delete wnd;
    delete[] backpack;
}

void people::addWand(wand *w, int n) {
    if (n >= maxWand || n < 0) return;
    this->wnd[n] = w;
}

bool people::addSpell(class::spell *spl) {
    for (int i = 0; i < backpackNum - 1; i++) {
        if (backpack[i] == nullptr) {
            backpack[i] = spl;
            return true;
        }
    }
    return false;
}

wand* people::getWand(int n) {
    if (n >= maxWand || n < 0) return nullptr;
    return wnd[n];
}

void people::draw(QPainter *painter) {
    painter->drawImage(QRectF(QPointF(body->GetPosition().x * PPM - this->getSize().x * PPM, body->GetPosition().y * PPM - this->getSize().y * PPM),
                             QPointF(body->GetPosition().x * PPM + this->getSize().x * PPM, body->GetPosition().y * PPM + this->getSize().y * PPM)), this->img);
}

class::spell* people::getPak(int n) {
    return backpack[n];
}

void people::swap(int wand1, int wand2, int spell1, int spell2) {
    //背包间交换
    if (wand1 == -1 && wand2 == -1) {
        auto tmp = backpack[spell1];
        backpack[spell1] = backpack[spell2];
        backpack[spell2] = tmp;
    }
    //与背包交换
    else if (wand1 == -1 || wand2 == -1) {
        if (wand1 == -1) {
            std::swap(wand1, wand2);
            std::swap(spell1, spell2);
        }
        auto tmp = wnd[wand1]->getSpell(spell1);
        wnd[wand1]->addSpell(backpack[spell2], spell1);
        backpack[spell2] = tmp;
    }
    //法杖间交换
    else if (spell1 == -1 || spell2 == -1) {
        auto tmp = wnd[wand1];
        wnd[wand1] = wnd[wand2];
        wnd[wand2] = tmp;
    }
    else {
        auto tmp = wnd[wand1]->getSpell(spell1);
        wnd[wand1]->addSpell(wnd[wand2]->getSpell(spell2), spell1);
        wnd[wand2]->addSpell(tmp, spell2);
    }

    //清除垃圾桶
    if (backpack[10] != nullptr) {
        delete backpack[10];
        backpack[10] = nullptr;
    }
}

void people::move(b2Vec2 pos) {};

void people::move(bool isPressed[]) {
    float xv = body->GetLinearVelocity().x;
    float yv = body->GetLinearVelocity().y;
    if (isPressed[0]) {
        if (xv >= -maxxSpeed) {
            if (xv > 0) body->ApplyForceToCenter(b2Vec2(-1000, 0), true);
            body->ApplyForceToCenter(b2Vec2(-1000, 0), true);
        } else {
        }
    }
    if (isPressed[3]) {
        if (xv <= maxxSpeed) {
            if (xv < 0) body->ApplyForceToCenter(b2Vec2(1000, 0), true);
            body->ApplyForceToCenter(b2Vec2(1000, 0), true);
        } else {
        }
    }
    if (isPressed['w' - 'a']) {
        if (jump > 0) {
            body->ApplyForceToCenter(b2Vec2(0, 600 + (maxySpeed - (yv > 0 ? yv : 0)) * 300), true);
            jump -= 0.5;
            onGround = false;
        }
    } else if (jump < 100){
        if (onGround) jump += 5;
        else jump += 0.1;
    }
}

void people::dead() {

}

void people::setOnGround() {
    onGround = true;
}

int people::getJump() {
    return jump;
}

int people::getMaxWand() {
    return maxWand;
}
