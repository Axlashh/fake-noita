#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include "others.h"

namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget(QWidget *parent = 0);
    ~gameWidget();
    Ui::gameWidget *ui;

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:


private:
    void initializeWorld();
    void createPlayer();
    void createMap();
    const float PPM = 30; //pixels per meter
    QTransform *transformer;
    QImage playerImg;
    QTimer *timer;
    b2World *world;
    people *player;
    b2Body *ground;
};

#endif // GAMEWIDGET_H

