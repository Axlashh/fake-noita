#include "wand.h"
#include "userData.h"

wand::~wand() {
    for (int i = 0; i < capacity; i++) {
        if (spl[i] != nullptr)
            delete spl[i];
    }
    delete[] spl;
}

class::spell* wand::getSpell(int n) {
    return spl[n];
}

int wand::getSpellNum() {
    return this->capacity;
}

normalWand::normalWand() {
    delay = 0;
    recharge = 0;
    bdelay = 12;
    brecharge = 24;
    maxMana = 120;
    mana = 120;
    manaChargeSpeed = 1;
    capacity = 5;
    spread = 10;
    pos = 0;
    spl = new class::spell*[capacity];
    isBack = false;
    for (int i = 0; i < capacity; i++) spl[i] = nullptr;
    img = QImage("../23su/source/image/wand_1.png").mirrored(false, true);
}

class::spell* wand::extract(mod m) {
    //回绕完毕
    if (isBack && pos == startPos)
        return nullptr;
    //寻找法力值支持释放的法术
    while (pos < capacity && (spl[pos] == nullptr || spl[pos]->getMana() > mana)) pos++;
    //进行回绕或者是抽取完毕
    if (pos == capacity) {
        isBack = true;
        pos = 0;
        return extract();
    }
    //消耗法力值
    this->mana -= spl[pos]->getMana();
    this->delay += spl[pos]->getCastDelay();
    this->recharge += spl[pos]->getRechargeTime();
    //抽取到的法术进行进一步计算
    class::spell *rt = spl[pos]->copy();
    pos++;
    rt->compute(this, m);
    return rt;
}

void wand::shoot(float x, float y, int degree, b2World *world) {
    startPos = pos;
    class::spell* t = extract();
    if (t == nullptr) return;
    //发射！
    t->compute(this);
    t->shoot(x, y, degree, world);
    delay += bdelay;
    recharge += brecharge;
    //防止施法延迟与充能时间变为负数
    delay = delay > 0 ? delay : 0;
    recharge = recharge > 0 ? recharge : 0;
    //法杖法术槽释放完一轮，进行充能
    if (pos == capacity || isBack) {
        isBack = true;
        pos = 0;
    }
}

void wand::update() {
    if (mana <= maxMana) mana += manaChargeSpeed;
    if (delay > 0) delay--;
    //如果处在充能状态
    if (isBack && recharge > 0) recharge--;

    //充能完毕
    if (recharge == 0) isBack = false;
}

bool wand::readyToShoot() {
    //施法延迟为0 且不处在充能状态
    return (delay == 0 && !isBack);
}

void wand::addSpell(class::spell* spl, int n) {
    this->spl[n] = spl;
}
