#-------------------------------------------------
#
# Project created by QtCreator 2018-04-27T09:59:19
#
#-------------------------------------------------

QT       += core gui opengl

RESOURCES += shaders.qrc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    widget.h

FORMS    += mainwindow.ui

#LIBS += -lopengl32

DEFINES += QT_DEPRECATED_WARNINGS
