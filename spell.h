#pragma once
#ifndef SPELL_H
#define SPELL_H

#include <QImage>
#include <QPainter>
#include <box2d/box2d.h>

#define projectile 	0
#define pmodifier 	1
#define multicast 	2
#define withTrigger	3

typedef struct mod {
    float sr, dr;
}mod;

class wand;

class spell
{
public:
    //法术发射
    //virtual ~spell();
    //计算本次法术释放的情况
    virtual void compute(wand *wd, mod m = {1, 1});
    virtual void shoot(float x, float y, int degree, b2World *world);
    //提供一个深复制的对象
    virtual spell* copy() = 0;
    virtual void draw(QPainter *painter, float PPM);

    int getMana();
    int getCastDelay();
    int getRechargeTime();

    void creatBody(float x, float y, b2World *world);
    void setV(int v, int degree);

protected:
//  法术类型
//  0 projectile 	为投射物
//  1 modifier 		为投射修正
//  2 multicast 	为多重释放
//	3 withTrigger	为带触发的法术
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
//	物体半径
    float r;
//	body
    b2Body *body;
//	物体基本信息
    b2BodyDef *bodyDef;
//	物体fixture
    b2FixtureDef *fixDef;
};

//	火花弹
class sparkBolt : public spell
{
public:
    sparkBolt();
    void draw(QPainter *painter, float PPM)	override;
    sparkBolt* copy()	override;
};

//	带触发的火花弹
class sparkBoltt : public sparkBolt
{
public:
    sparkBoltt();
    sparkBoltt* copy()	override;
};

//	能量球
class energyOrb : public spell
{
public:
    energyOrb();
    void draw(QPainter *painter, float PPM)	override;
    energyOrb* copy()	override;
};

//	带触发的能量球
class energyOrbt : public energyOrb
{
public:
    energyOrbt();
    energyOrbt* copy()	override;
};

//	链锯
class chain : public spell
{
public:
    chain();
    void draw(QPainter *painter, float PPM)	override;
    chain* copy()	override;
};

//	双重释放
class doubleSpell : public spell
{
public:
    doubleSpell();
    doubleSpell* copy()	override;
};

//	注入法力
class addMana : public spell
{
public:
    addMana();
    addMana* copy()	override;
};

//	加速
class speedUp : public spell
{
public:
    speedUp();
    speedUp* copy()	override;
};

//	伤害增强
class damagePlus : public spell
{
public:
    damagePlus();
    damagePlus* copy()	override;
};

#endif // SPELL_H
