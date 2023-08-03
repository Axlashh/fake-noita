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
    cv::Mat s(3, 3, CV_8UC1);
    cv::randu(s, cv::Scalar(0), cv::Scalar(255));
    displayImg(this->ui->gameLabel, s);
}

gameWidget::~gameWidget()
{
    delete ui;
}
