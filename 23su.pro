QT       += core gui
QT       += concurrent
QT       += core gui sql
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH +=  D:\AAAAAAA\documents\opencv\build\include\
                extern\

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    gameWidget.cpp \
    loginWidget.cpp \
    main.cpp \
    pauseWidget.cpp \
    people.cpp \
    registerWidget.cpp \
    spell.cpp \
    userData.cpp \
    wand.cpp

HEADERS += \
    character.h \
    gameWidget.h \
    loginWidget.h \
    pauseWidget.h \
    people.h \
    registerWidget.h \
    spell.h \
    userData.h \
    wand.h

FORMS += \
    gameWidget.ui \
    loginWidget.ui \
    pauseWidget.ui \
    registerWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    handTrack.py

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/extern/lib/ -lbox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/extern/lib/ -lbox2d
else:unix: LIBS += -L$$PWD/extern/lib/ -lbox2

INCLUDEPATH += $$PWD/extern
DEPENDPATH += $$PWD/extern
