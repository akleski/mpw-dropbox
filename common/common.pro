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
    nameresponsepacket.cpp \
    getserverfilespacket.cpp \
    getserverfilesresponsepacket.cpp \
    uploadfilespacket.cpp \
    uploadfilesresponsepacket.cpp \
    downloadfilespacket.cpp \
    downloadfilepacket.cpp \
    downloadfilesresponsepacket.cpp

HEADERS += dropboxpacket.h \
    namepacket.h \
    nameresponsepacket.h \
    getserverfilespacket.h \
    getserverfilesresponsepacket.h \
    uploadfilespacket.h \
    uploadfilesresponsepacket.h \
    downloadfilespacket.h \
    downloadfilepacket.h \
    downloadfilesresponsepacket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
