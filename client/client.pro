#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h

INCLUDEPATH += ../common
LIBS += -L../common/debug -lcommon
