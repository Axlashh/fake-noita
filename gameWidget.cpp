#include "gameWidget.h"
#include "ui_gameWidget.h"
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>

gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    connect(ui->quitButton, &QPushButton::clicked, this, [=](){
        this->hide();
    });
}

gameWidget::~gameWidget()
{
    delete ui;
}
