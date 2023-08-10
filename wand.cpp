#include "wand.h"

normalWand::normalWand() {
    bdelay = 12;
    brecharge = 24;
    maxMana = 120;
    mana = 120;
    manaChargeSpeed = 1;
    capacity = 5;
    spread = 10;
    pos = 0;
    spl = new spell*[capacity];
    isBack = false;
    for (int i = 0; i < capacity; i++) spl[i] = nullptr;
}

spell* wand::extract() {
    //回绕完毕
    if (isBack && pos == startPos)
        return nullptr;
    //寻找法力值支持释放的法术
    while (pos < capacity && spl[pos] != nullptr && spl[pos]->getMana() > mana) pos++;
    //进行回绕
    if (pos == capacity) {
        isBack = true;
        pos = 0;
        return extract();
    }
    //消耗法力值
    this->mana -= spl[pos]->getMana();
    //抽取到的法术进行进一步计算
    spl[pos]->compute(this);
    pos++;
}

void wand::shoot(float x, float y, int degree) {
    startPos = pos;
    spell* t = extract();
    if (t == nullptr) return;
    //发射！
    t->shoot(x, y, degree);
    //防止施法延迟与充能时间变为负数
    delay = delay > 0 ? delay : 0;
    recharge = recharge > 0 ? recharge : 0;
    //法杖法术槽释放完一轮，进行充能
    if (pos == capacity || isBack) {
        isBack = true;
        pos = 0;
    }
}
