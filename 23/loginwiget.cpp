include "loginwiget.h"
#include "ui_loginwiget.h"

loginwiget::loginwiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwiget)
{
    ui->setupUi(this);
}

loginwiget::~loginwiget()
{
    delete ui;
}
