#ifndef WAND_H
#define WAND_H

#include <QImage>
#include <vector>
#include "spell.h"

//typedef struct srd{
//    spell* s;
//    int r, d;
//}srd;

class wand
{
public:
    virtual ~wand();
    void shoot(float x, float y, int degree, b2World *world);
    class::spell* extract(mod m = {1, 1});
    void update();
    bool readyToShoot();
    void addSpell(class::spell* spl, int n);
    class::spell *getSpell(int n);
    int getSpellNum();
    //图片
    QImage img;

protected:
    //基础施法延迟,帧为单位
    int bdelay;
    //法杖实时的延迟，不为0则无法施法
    int delay;
    //基础充能时间
    int brecharge;
    //法杖实时的充能时间
    int recharge;
    //最大法力值
    int maxMana;
    //实时法力值
    int mana;
    //法力值恢复速率
    int manaChargeSpeed;
    //散射角度
    int spread;
    //容量
    int capacity;
    //目前抽取位置
    int pos;
    //一次发射时开始抽取的位置
    int startPos;
    //是否为回绕
    bool isBack;
    //法杖内所含法术
    class::spell **spl;

};

//普通的魔杖
class normalWand : public wand
{
public:
    normalWand();
};

//大容量魔杖
class longWand : public wand
{
public:
    longWand();
};

//小而快魔杖
class shortWand : public wand
{
public:
    shortWand();
};

#endif // WAND_H
