#ifndef USERDATA_H
#define USERDATA_H

const int PPM = 40;

enum userDataType {
    //法术
    spell,
    //怪物
    monster,
    //玩家
    player,
    //泛指地面
    ground
};

typedef struct userData {
    userDataType type;
    unsigned long long p;
}userData;


#endif // USERDATA_H
