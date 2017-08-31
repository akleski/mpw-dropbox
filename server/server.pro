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
    clientthread.cpp

HEADERS += \
    server.h \
    clientthread.h
