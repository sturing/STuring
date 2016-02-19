#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T10:10:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sturing3
TEMPLATE = app


SOURCES += main.cpp \
    controller.cpp \
    ui.cpp \
    sturing.cpp \
    codeeditor.cpp \
    history.cpp \
    historyitem.cpp \
    errorcontroller.cpp \
    filecontroller.cpp \
    localization.cpp \
    settings.cpp

HEADERS  += \
    controller.h \
    ui.h \
    sturing.h \
    codeeditor.h \
    history.h \
    historyitem.h \
    errorcontroller.h \
    filecontroller.h \
    localization.h \
    settings.h
CONFIG += c++11

RESOURCES += \
    resources.qrc \
    styles/style.qrc
