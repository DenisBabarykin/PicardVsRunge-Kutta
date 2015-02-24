#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T18:22:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PicarVsRungeKutta
TEMPLATE = app


SOURCES += main.cpp\
        MainForm.cpp \
    Picard.cpp \
    Runge-Kutta.cpp \
    CalcFunc.cpp

HEADERS  += MainForm.h \
    Picard.h \
    Timer.h \
    Runge-Kutta.h \
    CalcFunc.h

FORMS    += MainForm.ui

RESOURCES += \
    qdarkstyle/style.qrc
