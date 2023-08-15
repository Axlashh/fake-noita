#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

namespace Ui {
class registerWidget;
}

class registerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit registerWidget(QWidget *parent = nullptr);
    ~registerWidget();
signals:
    void mysignal();

private slots:
    void on_registerButton_clicked();

private:
    Ui::registerWidget *ui;
};

#endif // REGISTERWIDGET_H
