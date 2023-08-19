#include "wand.h"
#include "userData.h"
#include <QDebug>

wand::~wand() {
    for (int i = 0; i < capacity; i++) {
        if (spl[i] != nullptr)
            delete spl[i];
    }
    delete[] spl;
}

bool wand::readyToShoot() {
    //施法延迟为0 且不处在充能状态
    return (delay == 0 && !isBack);
}

void wand::addSpell(class::spell* spl, int n) {
    this->spl[n] = spl;
}

class::spell* wand::getSpell(int n) {
    return spl[n];
}

int wand::getSpellNum() {
    return this->capacity;
}

int wand::getMana() {
    return this->mana;
}

int wand::getRecharge() {
    return this->recharge;
}

int wand::getDelay() {
    return this->delay;
}

bool wand::roundDone() {
    for (int i = pos + 1; i < capacity; i++) {
        if (spl[i] != nullptr) {
            return false;
        }
    }
    pos = 0;
    return true;
}


class::spell* wand::extract(mod m, bool canBack) {
    //寻找法力值支持释放的法术
    while (pos < capacity && (spl[pos] == nullptr || spl[pos]->getMana() > mana)) pos++;
    //回绕完毕
    if (isBack && pos >= startPos)
        return nullptr;
    //进行回绕或者是抽取完毕
    if (pos == capacity) {
        isBack = true;
        pos = 0;
        if (canBack)
            return extract(m);
        return nullptr;
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
    t->shoot(x, y, degree, world);
    delay += bdelay;
    //防止施法延迟与充能时间变为负数
    delay = delay > 0 ? delay : 0;
    //防止法力超出上限
    mana = mana < maxMana ? mana : maxMana;
    //法杖法术槽释放完一轮，进行充能
    if (pos == capacity || isBack) {
        isBack = true;
        pos = 0;
        recharge += brecharge;
        recharge = recharge > 0 ? recharge : 0;
    }
}

void wand::update() {
    if (mana <= maxMana) mana += manaChargeSpeed;
    if (delay > 0) delay--;
    if (!isBack) {
    //检测接下来是否还有可释放的法术
        int i;
        for (i = pos; i < capacity; i++) {
            if (spl[i] != nullptr) {
                break;
            }
        }
        if (i == capacity) {
            isBack = true;
            pos = 0;
            recharge += brecharge;
        }
    }
    //如果处在充能状态
    if (isBack && recharge > 0) recharge--;

    //充能完毕
    if (isBack && recharge <= 0) {
        isBack = false;
        recharge = 0;
    }
}

normalWand::normalWand() {
    delay = 0;
    recharge = 0;
    bdelay = 12;
    brecharge = 30;
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

longWand::longWand() {
    delay = 0;
    recharge = 0;
    bdelay = 16;
    brecharge = 50;
    maxMana = 200;
    mana = 200;
    manaChargeSpeed = 1;
    capacity = 10;
    spread = 15;
    pos = 0;
    spl = new class::spell*[capacity];
    isBack = false;
    for (int i = 0; i < capacity; i++) spl[i] = nullptr;
    img = QImage("../23su/source/image/wand_3.png").mirrored(false, true);
}

shortWand::shortWand() {
    delay = 0;
    recharge = 0;
    bdelay = -5;
    brecharge = 10;
    maxMana = 80;
    mana = 80;
    manaChargeSpeed = 2;
    capacity = 3;
    spread = 6;
    pos = 0;
    spl = new class::spell*[capacity];
    isBack = false;
    for (int i = 0; i < capacity; i++) spl[i] = nullptr;
    img = QImage("../23su/source/image/wand_2.png").mirrored(false, true);
}
