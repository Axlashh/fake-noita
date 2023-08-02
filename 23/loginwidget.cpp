#include "loginwidget.h"
#include "ui_loginwidget.h"

loginwidget::loginwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwidget)
{
    ui->setupUi(this);
}

loginwidget::~loginwidget()
{
    delete ui;
}

void loginwidget::on_button2_clicked()
{
    w.show();
    this->hide();
}
