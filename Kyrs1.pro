#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T11:46:04
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kyrs1
TEMPLATE = app


SOURCES += main.cpp\
        diagrameditor.cpp \
    data.cpp \
    color.cpp \
    vsdata.cpp

HEADERS  += diagrameditor.h \
    data.h \
    color.h \
    vsdata.h

FORMS    += diagrameditor.ui

QTPLUGIN    +=qico
LIBS        +=-L$(QTDIR)/plugins/imageformats
