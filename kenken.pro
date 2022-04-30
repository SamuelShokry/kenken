#-------------------------------------------------
#
# Project created by QtCreator 2022-04-30T13:59:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kenken
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cage.cpp \
    cell.cpp \
    draw.cpp \
    grid.cpp \
    kenken.cpp \
    operationsCategory.cpp \
    framegui.cpp \
    cagebordersgui.cpp \
    gridgui.cpp

HEADERS  += mainwindow.h \
    cage.h \
    cell.h \
    draw.h \
    grid.h \
    kenken.h \
    operationsCategory.h \
    framegui.h \
    cagebordersgui.h \
    gridgui.h

FORMS    += mainwindow.ui
