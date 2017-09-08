#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = server
CONFIG   += qt console thread
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES *= QT_USE_QSTRINGBUILDER

SOURCES += main.cpp \
    server.cpp \
    clienthandler.cpp \
    storagecontroller.cpp \
    storageworker.cpp \
    storagetask.cpp

HEADERS += \
    server.h \
    clienthandler.h \
    storagecontroller.h \
    storageworker.h \
    storagetask.h


INCLUDEPATH += ../common
LIBS += -L../common/debug -lcommon
