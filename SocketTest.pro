#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T18:21:14
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocketTest
TEMPLATE = app

RC_FILE = res.rc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
