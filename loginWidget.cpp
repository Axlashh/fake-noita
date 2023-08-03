#include "loginWidget.h"
#include "ui_loginWidget.h"
#include "ui_gameWidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget),
    cf(new cutfruitThread())
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, [=](){
        w.show();
        this->hide();
        //cf->run();
        //Py_Initialize();
        //Py_Finalize();
    });
    cf->setLabel(w.ui->gameLabel);
}

loginWidget::~loginWidget()
{
    delete ui;
}
