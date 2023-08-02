#ifndef LOGINWIGET_H
#define LOGINWIGET_H

#include <QWidget>

namespace Ui {
class loginwiget;
}

class loginwiget : public QWidget
{
    Q_OBJECT

public:
    explicit loginwiget(QWidget *parent = 0);
    ~loginwiget();

private:
    Ui::loginwiget *ui;
};

#endif // LOGINWIGET_H
