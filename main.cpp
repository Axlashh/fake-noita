#include "gameWidget.h"
#include <QApplication>
#include"loginWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginWidget w;
    w.show();

    return a.exec();
}
