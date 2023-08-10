#ifndef WAND_H
#define WAND_H


class wand
{
public:
    wand();
    void shoot();

protected:
    //施法延迟,帧为单位
    int delay;
    //充能时间
    int recharge;
    //最大法力值
    int mana;
    //法力值恢复速率
    int manaChargeSpeed;
    //散射角度
    int spread;
    //容量
    int capacity;


};

#endif // WAND_H
