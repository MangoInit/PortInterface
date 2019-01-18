#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T17:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = port_public
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    port_public_dialog.cpp

HEADERS  += mainwindow.h \
    port_public_dialog.h

FORMS    += mainwindow.ui \
    port_public_dialog.ui

QT += serialport
