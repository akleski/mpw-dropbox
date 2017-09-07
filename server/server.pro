#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    clientthread.cpp \
    workerthread.cpp

HEADERS += \
    server.h \
    clientthread.h \
    workerthread.h


INCLUDEPATH += ../common
LIBS += -L../common/debug -lcommon
