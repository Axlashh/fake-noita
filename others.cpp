#include "others.h"
#include <iostream>

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

cutfruitThread::cutfruitThread(QLabel *label) : label(label) {}

void cutfruitThread::setLabel(QLabel *label) {
    this->label = label;
}

void cutfruitThread::run() {
    std::cout<<666<<std::endl;
    PyGILState_STATE gstate = PyGILState_Ensure();
    Py_Initialize();

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    pModule = PyImport_ImportModule("handTrack");
    pFunc = PyObject_GetAttrString(pModule, "getCamera");
    PyObject* pArgs = PyTuple_New(0);

    //while (1) {
    PyObject* pReturn = PyObject_CallObject(pFunc, pArgs);
    PyArrayObject* pArray = reinterpret_cast<PyArrayObject*>(pReturn);
    cv::Mat pic(PyArray_DIM(pArray, 0), PyArray_DIM(pArray, 1), CV_8UC3, PyArray_DATA(pArray));
    displayImg(label, pic);
    //}
    Py_Finalize();
    PyGILState_Release(gstate);
}
