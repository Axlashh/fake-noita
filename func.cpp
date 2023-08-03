#include "func.h"

void displayImg(QLabel *label, cv::Mat &mat) {
    QImage img;
    if (mat.channels() == 3) {
        cv::Mat rgb;
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        img = QImage((const uchar*)(rgb.data), rgb.cols, rgb.rows, rgb.cols * rgb.channels(), QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(img));
}
