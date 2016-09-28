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
        pcars/pcarsThread.cpp \
    serialcom/serialcom.cpp \
    loopthread.cpp \
    serialcom/serialthread.cpp

HEADERS  += mainwindow.h \
    pcars/pcarssharedmemory.h \    
    pcars/pcarsThread.h \
    gameData.h \
    serialcom/serialcom.h \
    loopthread.h \
    serialcom/serialthread.h

FORMS    += mainwindow.ui

DISTFILES += \
    .gitattributes \
    .gitignore
