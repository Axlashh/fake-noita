#ifndef OTHERS_H
#define OTHERS_H

#include <QImage>
#include <QLabel>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QMainWindow>
#include <box2d/box2d.h>

class Box2DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Box2DWidget(QWidget *parent = nullptr);
    ~Box2DWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initializeWorld();
    void createGround();
    void createBall(float x, float y, float radius);

    QTimer *timer;
    b2World *world;
    b2Body *ground;
    b2Body *ball;
};

#endif // OTHERS_H
