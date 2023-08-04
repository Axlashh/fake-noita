#include "loginWidget.h"
#include "ui_loginWidget.h"
#include "ui_gameWidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, [=](){
        w.show();
        this->hide();
    });
}

loginWidget::~loginWidget()
{
    delete ui;
}
