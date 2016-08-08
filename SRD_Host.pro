#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T19:26:56
#
#-------------------------------------------------

QT       += core gui \
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SRD_Host
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pcars/pcarsworker.cpp \
    dashboard/pixmaps/defaultmonitor.cpp \
    dashboard/pixmaps/textframe.cpp \
    dashboard/dashboard.cpp \
    dashboard/pixmaps/dashboardcontent.cpp \
    dashboard/dashboardthread.cpp \
    dashboard/pixmaps/damagemonitor.cpp

HEADERS  += mainwindow.h \
    pcars/pcarsworker.h \
    pcars/pcarssharedmemory.h \
    clientData.h \
    dashboard/pixmaps/defaultmonitor.h \
    dashboard/pixmaps/settings.h \
    dashboard/pixmaps/textframe.h \
    dashboard/dashboard.h \
    dashboard/pixmaps/dashboardcontent.h \
    dashboard/dashboardthread.h \
    dashboard/pixmaps/damagemonitor.h

FORMS    += mainwindow.ui
