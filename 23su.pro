QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH +=  D:\AAAAAAA\documents\opencv\build\include\
                D:\AAAAAAA\documents\opencv\build\include\opencv2\
                C:\Users\Axlash\AppData\Local\Programs\Python\Python39\include\
                C:\Users\Axlash\AppData\Local\Programs\Python\Python39\Lib\site-packages\numpy\core\include\



LIBS += -L D:\AAAAAAA\documents\opencv\build\x64\MinGW\lib\libopencv_*.a
LIBS += -LC:\Users\Axlash\AppData\Local\Programs\Python\Python39\libs\ -lpython39 -l_tkinter -lpython3

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameWidget.cpp \
    loginWidget.cpp \
    main.cpp \
    others.cpp \
    registerwidget.cpp

HEADERS += \
    gameWidget.h \
    loginWidget.h \
    others.h \
    registerwidget.h

FORMS += \
    gameWidget.ui \
    loginWidget.ui \
    registerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    handTrack.py
