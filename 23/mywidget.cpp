#include "mywidget.h"
#include "ui_mywidget.h"
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
}

myWidget::~myWidget()
{
    delete ui;
}


void myWidget::on_button2_clicked()
{
    hide();
}
