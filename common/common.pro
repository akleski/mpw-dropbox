#-------------------------------------------------
#
# Project created by QtCreator 2017-09-01T09:19:57
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = common
TEMPLATE = lib
CONFIG += staticlib

SOURCES += dropboxpacket.cpp \
    namepacket.cpp \
    clientfilespacket.cpp \
    clientfilesresppacket.cpp

HEADERS += dropboxpacket.h \
    namepacket.h \
    clientfilespacket.h \
    clientfilesresppacket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
