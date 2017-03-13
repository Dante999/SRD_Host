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
    serialcom/serialcom.cpp \
    loopthread.cpp \
    game.cpp \
    pcars/pcars.cpp

HEADERS  += mainwindow.h \
    pcars/pcarssharedmemory.h \    
    gameData.h \
    serialcom/serialcom.h \
    loopthread.h \
    game.h \
    pcars/pcars.h

FORMS    += mainwindow.ui

DISTFILES += \
    .gitattributes \
    .gitignore
