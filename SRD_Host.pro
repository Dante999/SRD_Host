#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T19:26:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SRD_Host
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    sharedmemory.h \
    struct_data.h

FORMS    += mainwindow.ui
