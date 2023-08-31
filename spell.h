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
    virtual ~spell();
    //计算本次法术释放的情况
    virtual void compute(wand *wd, mod m = {1, 1});
    virtual void shoot(float x, float y, int degree, b2World *world);
    //提供一个深复制的对象
    virtual spell* copy();
    //绘图函数
    virtual void draw(QPainter *painter);
    //获取该法术的图标
    QImage* getimg();
    //法术爆炸
    virtual void bomb();
    virtual void bomb(int deg);
    //返回法术是否该被销毁
    bool dead();
    //返回法术是否会对玩家造成伤害
    bool safe();

    QString getName();
    QString getExtraInfo();
    int getType();
    int getManaCast();
    int getDamage();
    int getSpeed();
    int getSpread();
    int getLifetime();
    int getDelay();
    int getRechargeTime();
    float getSpeedRate();
    float getDamageRate();
    float getR();

    void creatBody(float x, float y, b2World *world, int deg);
    void setV(int v, int degree);

protected:
    void copyTo(spell* t);
    //名称
    QString name;
    //额外说明信息
    QString extraInfo;
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
//  持续时间，以帧为单位, 带定时效果法术用的
    int lifetime;
//  施放延迟
    int delay;
//  充能时间
    int rechargeTime;
//	速度修正倍率
    float speedRate;
//	伤害修正倍率
    float damageRate;
//	该法术将触发的法术
    spell **spl = nullptr;
//	图片
    QImage img;
//	爆炸图片
    QImage bombImg;
//	发射时显示的图片
    QImage shootImg;
//	物体半径
    float r;
//	body
    b2Body *body = nullptr;
    b2BodyUserData *ud = nullptr;
//	物体基本信息
    b2BodyDef *bodyDef = nullptr;
//	物体fixture
    b2FixtureDef *fixDef = nullptr;

//	爆炸后绘图需要的变量
    bool isBomb;
    int bombTime;
    bool isDead;
    bool isSafe;
//	带有触发的法术是否已触发
    bool triggerShooted;
    b2Vec2 triggerPos;
    int triggerDeg;

//	物体在发射状态的绘图框
    QRectF shootRec;
//	物体在爆炸状态的绘图框
    QRectF bombRec;
};

//	火花弹
class sparkBolt : public spell
{
public:
    sparkBolt();
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
    energyOrb* copy()	override;
};

//	带触发的能量球
class energyOrbt : public energyOrb
{
public:
    energyOrbt();
    energyOrbt* copy()	override;
};

//	链锯(其实应该叫电火花)
class chain : public spell
{
public:
    chain();
    chain* copy()	override;
    void draw(QPainter *painter)	override;

private:
    QImage *imgs;
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

class slimeBall : public spell
{
public :
    slimeBall();
    slimeBall* copy()	override;
};

#endif // SPELL_H
