#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>

namespace Ui {
class pauseWidget;
}

class pauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pauseWidget(QWidget *parent = nullptr);
    ~pauseWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::pauseWidget *ui;
};

#endif // PAUSEWIDGET_H
