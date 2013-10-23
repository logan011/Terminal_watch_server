#-------------------------------------------------
#
# Project created by QtCreator 2013-09-11T15:18:20
#
#-------------------------------------------------

QT       += core gui network
QT      +=sql
TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    database.cpp

HEADERS  += widget.h \
    database.h

FORMS    += widget.ui

OTHER_FILES += \
    CssStyle
