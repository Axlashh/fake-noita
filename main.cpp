#include "gameWidget.h"
#include <QApplication>
#include "loginWidget.h"
#include "userData.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont("../23su/source/IPix.ttf");
    gameWidget aaa;
    aaa.show();
//  loginWidget k;
//    k.show();

    return a.exec();
}
