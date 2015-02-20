TEMPLATE = app
QT += gui widgets network \
    xml \
    webkit webkitwidgets

HEADERS += mainwindow.h
SOURCES += main.cpp \
    mainwindow.cpp

include(../pods.pri)
