#include "gameWidget.h"
#include <QApplication>
#include "loginWidget.h"
#include "others.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    gameWidget aaa;
//    aaa.show();
    loginWidget k;
    k.show();

    return a.exec();
}
