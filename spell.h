#ifndef SPELL_H
#define SPELL_H

#include <QImage>
#include <box2d/box2d.h>

#define projectile 0
#define multicast 1
#define pmodifier 2
#define pjtWithTrigger 3

class wand;

class spell
{
public:
    //法术发射
    virtual void shoot(float x, float y, int degree) = 0;
    //计算本次法术释放的情况
    virtual void compute(wand *wd);
    int getMana();

protected:
//  法术类型
//  0 projectile 为投射物
//  1 multicast 为多重释放
//  2 modifier 为投射修正
//	3 为带触发的投射物
    int type;
//  额外抽取的法术个数
    int drawNum;
//  法术消耗
    int manaCast;
//  伤害
    int damage;
//  速度
    int speed;
//  散射角度
    int spread;
//  持续时间，以帧为单位
    int lifetime;
//  施放延迟
    int castDelay;
//  充能时间
    int rechargeTime;
//	速度修正倍率
    float speedRate;
//	伤害修正倍率
    float damageRate;
//	该法术将触发的法术
    spell **spl;
//	图片
    QImage img;
};

//	火花弹
class sparkBolt : public spell
{
public:
    sparkBolt();
    void shoot(float x, float y, int degree)	override;
};

//	带触发的火花弹
class sparkBoltt : public spell
{
public:
    sparkBoltt();
    void shoot(float x, float y, int degree)	override;
};

//	能量球
class energyOrb : public spell
{
public:
    energyOrb();
    void shoot(float x, float y, int degree)	override;
};

//	带触发的能量球
class energyOrbt : public spell
{
public:
    energyOrbt();
    void shoot(float x, float y, int degree)	override;
};

//	链锯
class chain : public spell
{
public:
    chain();
    void shoot(float x, float y, int degree)	override;
};

//	双重释放
class doubleSpell : public spell
{
public:
    doubleSpell();
    void shoot(float x, float y, int degree)	override;
};

//	注入法力
class addMana : public spell
{
public:
    addMana();
    void shoot(float x, float y, int degree)	override;
};

//	加速
class speedUp : public spell
{
public:
    speedUp();
    void shoot(float x, float y, int degree)	override;
};

//	伤害增强
class damagePlus : public spell
{
public:
    damagePlus();
    void shoot(float x, float y, int degree)	override;
};

#endif // SPELL_H
