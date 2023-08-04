#include "gameWidget.h"
#include "ui_gameWidget.h"
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>

gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    connect(ui->quitButton, &QPushButton::clicked, this, [=](){
        this->hide();
    });
    Box2DWidget a(this);
}

gameWidget::~gameWidget()
{
    delete ui;
}
