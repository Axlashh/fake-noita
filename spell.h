#ifndef SPELL_H
#define SPELL_H

#include <QImage>

#define projectile 0
#define multicast 1
#define modifier 2


class spell
{
public:
    spell();

protected:
//  法术类型
//  0 projectile 为投射物
//  1 multicast 为多重释放
//  2 modifier 为投射修正
    int type;
//  额外抽取的法术个数
    int drawNum;
//  法术消耗
    float manaCast;
//  伤害
    float damage;
//  速度
    float speed;
//  散射角度
    float spread;
//  持续时间，以帧为单位
    int lifetime;
//  施放延迟
    int castDelay;
//  充能时间
    int rechargeTime;
//	图片地址
    QImage img;
};

//	火花弹
class sparkBolt : public spell
{
public:
    sparkBolt();
};

//	能量球
class energyOrb : public spell
{
public:
    energyOrb();
};

#endif // SPELL_H
