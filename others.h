#ifndef OTHERS_H
#define OTHERS_H

#include <QImage>
#include <QLabel>
#include <opencv.hpp>
#include <Python.h>
#include <QThread>
#include <QDebug>
#include <numpy/arrayobject.h>

void displayImg(QLabel *label, cv::Mat &mat);

void cutFruit(QLabel *label);

class cutfruitThread : public QThread
{
public:
    cutfruitThread(QLabel *label = nullptr);
    void setLabel(QLabel *label);

    void run() override;

private:
    QLabel *label;
};

#endif // OTHERS_H
