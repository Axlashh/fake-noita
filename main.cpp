#include "gameWidget.h"
#include <QApplication>
#include "loginWidget.h"
#include "others.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameWidget aaa;
    aaa.show();
//    loginWidget w;
//    w.show();

    return a.exec();
}
