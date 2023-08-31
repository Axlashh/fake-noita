#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include <QtEvents>
#include <QPoint>
#include <QImage>
#include <QLabel>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QMainWindow>
#include <QMatrix>
#include <QTransform>
#include <QDir>
#include <QKeyEvent>

#include <character.h>
#include <people.h>
#include <monster.h>
#include <math.h>
#include <box2d/box2d.h>
#include "userData.h"
#include "pauseWidget.h"
#include "rewardwidget.h"

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
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event)	override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:


private:
    void initializeWorld();
    void createPlayer();
    void createMap();
    void playerMove();
    void wandUpdate();
    void monsterUpdate();
    void myUpdate();
    void start();
    QTransform *transformer;
    QImage playerImg;
    QTimer *timer;
    b2World *world;
    people *player;
    b2Body *ground;
    bool isPaused;
    pauseWidget *menu;
    rewardWidget *rwd;
    bool rwdupd;
    QPixmap bufferPixmap;

    //前26个代表字母，第27个代表鼠标
    bool isPressed[27] = {};

    QPoint mousePos;
    //人物到鼠标的角度
    int degree;
    float radian;

    int zombieRefresh;
    const int zr = 210;
    int greenCutieRefresh;
    const int gr = 600;

    int killAmount;
    QLabel *killAmountLabel;
};

class playerContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;
    people *player;
};

#endif // GAMEWIDGET_H

