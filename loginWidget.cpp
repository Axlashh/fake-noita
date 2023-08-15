#include "loginWidget.h"
#include "ui_loginWidget.h"

#include<QPushButton>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
#include<QMessageBox>
#include<QDebug>
//#include<QTableView>
loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget)
{

    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../23su/source/loginData");
    if(!db.open())
        qDebug()<<"can't open";
    else
        qDebug()<<"open";

    QString qs=QString("create table if not exists user(accountname ntext unique not NULL,passwordname ntext not NULL)");
    QSqlQuery query;
    if(query.exec(qs))
        qDebug()<<"ok";
    else
        qDebug()<<"no";
    connect(&ww,&registerWidget::mysignal,this,[=]()
            {
               this->show();
             });
}

loginWidget::~loginWidget()
{
    delete ui;
}
void loginWidget::on_registerButton_clicked()
{
    this->hide();
    ww.show();
}



void loginWidget::on_loginButton_clicked()
{

    QString account=ui->accountEdit->text();
    QString password=ui->passwordEdit->text();

    QString sqlname=QString("select * from user where accountname ='%1'")
                          .arg(account);
    QString sqlword=QString("select passwordname from user where accountname ='%1'")
                          .arg(account);

    QSqlQueryModel *model=new QSqlQueryModel;

    model->setQuery(sqlname);
    QModelIndex index1 = model->index(0,0);
    model->setQuery(sqlword);
    QModelIndex index2 = model->index(0,0);

    if(index1.data() == 0 || index2.data() != password)
    {
        QMessageBox::information(this,"登录","登录失败");
    }
    if(index1.data() != 0 && index2.data() == password)
    {
        QMessageBox::information(this,"登录","登录成功");
    }
}


void loginWidget::on_pushButton_clicked()
{
    /*QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery("select *from user");
    model->setHeaderData(0,Qt::Horizontal,tr("accountname"));
    model->setHeaderData(1,Qt::Horizontal,tr("passwordname"));
    QTableView *view=new QTableView;
    view->setModel(model);
    view->show();*/
}

