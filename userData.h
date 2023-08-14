#ifndef USERDATA_H
#define USERDATA_H

enum userDataType {
    spell,
    monster,
    player
};

typedef struct userData {
    userDataType type;
    unsigned long long p;
}userData;


#endif // USERDATA_H
