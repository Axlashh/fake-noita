#include "mywidget.h"
#include <QApplication>
#include"loginwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginwidget w;
    w.show();

    return a.exec();
}
