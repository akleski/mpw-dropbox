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

DEFINES *= QT_USE_QSTRINGBUILDER

SOURCES += main.cpp \
    server.cpp \
    workerthread.cpp \
    clienthandler.cpp \
    clientworker.cpp

HEADERS += \
    server.h \
    workerthread.h \
    clienthandler.h \
    clientworker.h


INCLUDEPATH += ../common
LIBS += -L../common/debug -lcommon
