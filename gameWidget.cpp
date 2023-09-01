#include "gameWidget.h"
#include "ui_gameWidget.h"
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>
#include <qnamespace.h>
#include <cmath>
#include "tile.h"
#include "pausewidget.h"


gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    isPaused = true;
    initializeWorld();
    bufferPixmap = QPixmap(size());
    bufferPixmap.fill(Qt::white);

    wand* aaaa = new normalWand();
    wand* pppp = new longWand();
    aaaa->addSpell(new chain(), 0);
    aaaa->addSpell(new doubleSpell(), 1);
    aaaa->addSpell(new chain(), 2);
    aaaa->addSpell(new sparkBoltt(), 3);
    aaaa->addSpell(new energyOrb(), 4);
    pppp->addSpell(new addMana(), 0);
    pppp->addSpell(new doubleSpell(), 1);
    pppp->addSpell(new speedUp(), 2);
    pppp->addSpell(new damagePlus(), 3);
    pppp->addSpell(new addMana(), 4);
    pppp->addSpell(new chain(), 5);
    pppp->addSpell(new sparkBolt(), 6);
    pppp->addSpell(new energyOrbt(), 7);
    pppp->addSpell(new doubleSpell(), 8);
    pppp->addSpell(new sparkBolt(), 9);
    player->addWand(aaaa, 0);
//    player->addWand(pppp, 1);
    backgroundImg = QImage("../23su/source/image/background.png").mirrored();

    menu = new pauseWidget(this, player);
    menu->hide();

    bnw = new beginWidget(this);
    connect(bnw, &beginWidget::ok, this, &gameWidget::start);
    dew = new deadWidget(this);
    dew->hide();
    rwd = new rewardWidget(this, player);
    rwd->hide();
    rwdW = new rewardWidget(this, player, slotType::wad);
    rwdW->hide();
    wandReward = true;
    rwdupd = false;
    connect(rwd, &rewardWidget::ok, this, &gameWidget::start);
    connect(rwdW, &rewardWidget::ok, this, &gameWidget::start);
    zombieRefresh = 0;
    greenCutieRefresh = 0;
    killAmount = 0;
    QFont font;
    font.setFamily("IPix");
    killAmountLabel = new QLabel(this);
    killAmountLabel->setFont(font);
    killAmountLabel->setGeometry(500, 10, 300, 30);
    killAmountLabel->setText("杀敌数:" + QString::number(killAmount));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        if (!isPaused) {
        myUpdate();
        }
        update();
    });
    timer->start(1000 / 60); // 设置更新频率为 60 Hz

}

gameWidget::~gameWidget()
{
    delete ui;
}

void gameWidget::paintEvent(QPaintEvent* event) {

    QPainter painter(&bufferPixmap);
    painter.translate(0, height());
    painter.scale(1, -1);

    painter.setRenderHint(QPainter::Antialiasing, true);

//    计时器的槽函数如果把update()放在里面，那么暂停换法杖时，暂停页面不会立马刷新
//    但如果把update()放在外面，带计时的法术就不会暂停，所以只能在这里加判断isPaused
//    很无语，不知道qt犯什么毛病
//	  还用了一个缓冲pixmap来储存绘出的图，不然一暂停游戏画面就没了
    if (!isPaused) {
        // 清空背景
        painter.drawImage(rect(), backgroundImg);

        //绘制世界中的人物和法术
        for (auto it = world->GetBodyList(); it != nullptr;) {
            struct::userData* ud = reinterpret_cast<struct::userData*>(it->GetUserData().pointer);
            switch (ud->type) {
             case userDataType::player:
                reinterpret_cast<people*>(ud->p)->draw(&painter);
                it = it->GetNext();
                break;
            case userDataType::spell:
                reinterpret_cast<class::spell*>(ud->p)->draw(&painter);
                it = it->GetNext();
                if (reinterpret_cast<class::spell*>(ud->p)->dead()) {
                    delete reinterpret_cast<class::spell*>(ud->p);
                }
                break;
            case userDataType::ground:
                reinterpret_cast<tile*>(ud->p)->draw(&painter);
                it = it->GetNext();
                break;
            case userDataType::monster:
                reinterpret_cast<character*>(ud->p)->draw(&painter);
                it = it->GetNext();
                break;
            default:
                it = it->GetNext();
                break;
            }
        }

        //绘制法杖
        auto tw = player->getWand(0);
        if (tw != nullptr) {
            painter.save();
            painter.translate(player->getPos().x * PPM, player->getPos().y * PPM);
            painter.rotate(degree);
            painter.drawImage(QRectF(QPointF(0, -0.2 * PPM), QPointF(1.3 * PPM, 0.2 * PPM)), tw->img);
            painter.restore();
            painter.save();
            painter.translate(width(), 0);
            painter.scale(-1, 1);
            painter.fillRect(QRect(0, height() - 20, tw->getMana(), 20), Qt::blue);
            painter.fillRect(QRect(0, height() - 40, tw->getRecharge(), 20), Qt::red);
            painter.fillRect(QRect(0, height() - 60, tw->getDelay(), 20), Qt::yellow);
            painter.restore();
        }

        //绘制jump框
        painter.fillRect(QRect(0, height() - 20, player->getJump(), 20), Qt::yellow);
        //绘制血条
        painter.fillRect(QRect(0, height() - 40, player->getBlood(), 20), Qt::red);
    }

    QPainter realPainter(this);
    realPainter.drawPixmap(0, 0, bufferPixmap);
}

void gameWidget::initializeWorld() {
    b2Vec2 gravity(0, -9.8f);
    world = new b2World(gravity);

    //创建玩家
    b2Vec2 pos(10.0f, 10.0f);
    player = new people(world, pos);

    createMap();
    playerContactListener *pcl = new playerContactListener();
    pcl->player = player;
    world->SetContactListener(pcl);
}

void gameWidget::createMap() {
    new tile(world, 16, 1, 16, 0.5);
    new tile(world, 8, 4, 2, 0.25);
    new tile(world, -1, 10, 1, 11);
    new tile(world, 33, 10, 1, 11);
}

void gameWidget::myUpdate() {
    //获取此帧鼠标的角度
    radian = std::atan2(height() - mousePos.y() - player->getPos().y * PPM, mousePos.x() - player->getPos().x * PPM);
    degree = radian * (180.0 / M_PI);

    //计算人物移动
    player->move(isPressed, mousePos);

    wandUpdate();
    monsterUpdate();

    world->Step(1.0f / 60.0f, 6, 2);

    if (zombieRefresh++ >= zr) {
        zombieRefresh = 0;
        new zombie(world, b2Vec2(rand() % 36, 10.0f));
    }

    if (greenCutieRefresh++ >= gr) {
        greenCutieRefresh = 0;
        new greenCutie(world, b2Vec2(rand() % 36, 15.0f));
    }

    if (killAmount % 3 != 0) {
        rwdupd = false;
    }

    if (wandReward && killAmount >= 20) {
        wandReward = false;
        isPaused = true;
        rwdW->show();
    }
    if(player->getBlood() <= 0)
    {
        isPaused=true;
         dew->show();
    }
}

void gameWidget::start() {
    isPaused = false;
}

void gameWidget::wandUpdate() {
    //对玩家的每根法杖进行更新
    for (int i = 0; i < player->getMaxWand(); i++) {
        if (player->getWand(i) != nullptr) {
            player->getWand(i)->update();
        }
    }
    auto wd = player->getWand(0);
    //如果鼠标左键被按下，发射！
    if (isPressed[26] && wd->readyToShoot()) {
        float cs = cos(radian), sn = sin(radian), xx = player->getPos().x, yy = player->getPos().y;
        wd->shoot(xx + 1.3 * cs, yy + 1.3 * sn, degree, world);
    }
}

//对每个怪物进行更新
void gameWidget::monsterUpdate(){
    for (auto it = world->GetBodyList(); it != nullptr;) {
        struct::userData* ud = reinterpret_cast<struct::userData*>(it->GetUserData().pointer);
        if (ud->type == userDataType::monster) {
            auto tp = reinterpret_cast<character*>(ud->p);
             tp->update(player->getPos());
            if (tp->getDead()) {
                killAmount++;

                if (!rwdupd && killAmount != 0 && (killAmount) % 3 == 0) {
                    isPaused = true;
                    rwdupd = true;
                    rwd->myUpdate();
                    rwd->show();
                }

                auto tmp = it;
                world->DestroyBody(tmp);
                delete tp;
                it = it->GetNext();
                continue;
            }

        }
        it = it->GetNext();      
    }
    killAmountLabel->setStyleSheet("color:rgb(255,255,255)");
    killAmountLabel->setText("杀敌数:" + QString::number(killAmount));
}

void gameWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = true;
    if (key == Qt::Key_Escape) {
        if (isPaused) {
            menu->hide();
            isPaused = false;
        } else {
            menu->myUpdate();
            menu->update();
            QCoreApplication::processEvents();
            menu->show();
            isPaused = true;
        }
    }
}

void gameWidget::keyReleaseEvent(QKeyEvent *event){
    int key = event->key();
    if (key >= 0x41 && key <= 0x5a) isPressed[key - 0x41] = false;
}

void gameWidget::mousePressEvent(QMouseEvent *event) {
    isPressed[26] = true;
}

void gameWidget::mouseReleaseEvent(QMouseEvent *event) {
    isPressed[26] = false;
}

void gameWidget::mouseMoveEvent(QMouseEvent *event) {
    setMouseTracking(true);
    mousePos = event->pos();
}

void playerContactListener::BeginContact(b2Contact *contact) {
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    userData* udA = reinterpret_cast<userData*>(bodyA->GetUserData().pointer);
    userData* udB = reinterpret_cast<userData*>(bodyB->GetUserData().pointer);
    if (((udA->type == userDataType::player || udA->type == userDataType::monster) &&
        udB->type == userDataType::ground && bodyA->GetPosition().y > bodyB->GetPosition().y) ||
        ((udB->type == userDataType::player || udB->type == userDataType::monster) &&
        udA->type == userDataType::ground && bodyB->GetPosition().y > bodyA->GetPosition().y)) {
         //活物与地面相撞
        if (udB->type == userDataType::ground)
            reinterpret_cast<character*>(udA->p)->setOnGround();
        else
            reinterpret_cast<character*>(udB->p)->setOnGround();
    } else if (udA->type == userDataType::spell && udB->type == userDataType::spell) {
        //法术与法术相撞
        contact->SetEnabled(false);
    } else if (udA->type == userDataType::spell || udB->type == userDataType::spell) {
        //法术与别的物体相撞
        if (udB->type == userDataType::spell) {
            auto tmp = udB;
            udB = udA;
            udA = tmp;
        }
        class::spell* s = reinterpret_cast<class::spell*>(udA->p);
        if (udB->type == userDataType::ground) {
            b2Vec2 nor = contact->GetManifold()->localNormal;
            int deg = std::atan2(nor.y, nor.x) * 180.0 / M_PI;
            s->bomb(deg);
        }
        else {
            s->bomb();
            if ((!s->safe() && udB->type == userDataType::player) || udB->type == userDataType::monster) {
                character* ch = reinterpret_cast<character*>(udB->p);
                ch->hurt(s->getDamage());
            }
        }
    } else if (udA->type == userDataType::monster || udB->type == userDataType::monster) {
        if (udB->type == userDataType::monster) {
            auto tmp = udB;
            udB = udA;
            udA = tmp;
        }
        character* mon = reinterpret_cast<character*>(udA->p);
        //怪物与人相撞
        if (udB->type == userDataType::player) {
            character* ch = reinterpret_cast<character*>(udB->p);
            ch->hurt(mon->getDamage());
        }
    }
}
