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

SOURCES += dropboxpacket.cpp

HEADERS += dropboxpacket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
