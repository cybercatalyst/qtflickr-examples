TEMPLATE = app

QT += gui widgets network xml

HEADERS += mainwindow.h \
    photo.h

SOURCES += main.cpp \
    mainwindow.cpp \
    photo.cpp

include(../pods.pri)
