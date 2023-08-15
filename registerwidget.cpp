#include "registerwidget.h"
#include "ui_registerWidget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    ui->account->setEchoMode(QLineEdit::Normal);
    ui->account->setPlaceholderText("账户");
    ui->password1->setEchoMode(QLineEdit::Password);
    ui->password1->setPlaceholderText("密码");
    ui->password2->setEchoMode(QLineEdit::Password);
    ui->password2->setPlaceholderText("确认密码");
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::on_registerButton_clicked()
{
    QString account=ui->account->text();
    QString password1=ui->password1->text();
    QString password2=ui->password2->text();
    QSqlQuery query;
    if(password1==password2&&password1!=nullptr&&account!=nullptr)
    {
     QString sql=QString("insert into user(accountname,passwordname) values('%1','%2');")
                      .arg(account).arg(password1);
      if(query.exec(sql))
      {
        qDebug()<<"right";
        QMessageBox::information(this,"注册","注册成功");
        emit mysignal();
        this->hide();
      }
      else
      {
        qDebug()<<"error";
        QMessageBox::information(this,"注册","注册失败");
      }
    }
    else
      QMessageBox::information(this,"注册","注册失败");
}

