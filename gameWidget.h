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
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:


private:
    void initializeWorld();
    void createPlayer();
    void createMap();
    void playerMove();
    const float PPM = 50; //pixels per meter
    QTransform *transformer;
    QImage playerImg;
    QTimer *timer;
    b2World *world;
    people *player;
    b2Body *ground;

    bool isPressed[26] = {};

    QThread *keyThread;
};

class playerContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;
    people *player;
};

#endif // GAMEWIDGET_H

