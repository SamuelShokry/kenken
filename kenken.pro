#-------------------------------------------------
#
# Project created by QtCreator 2022-04-30T13:59:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kenken
TEMPLATE = app

HEADERS += \
    back/cage.h \
    back/cell.h \
    back/draw.h \
    back/grid.h \
    back/kenken.h \
    back/operationsCategory.h \
    front/cagebordersgui.h \
    front/framegui.h \
    front/mainwindow.h \
    front/gridgui.h \
    front/gameview.h \
    front/targetgui.h \
    front/gamegui.h \
    front/gamesolngui.h

SOURCES += \
    back/cage.cpp \
    back/cell.cpp \
    back/draw.cpp \
    back/grid.cpp \
    back/kenken.cpp \
    back/operationsCategory.cpp \
    front/cagebordersgui.cpp \
    front/framegui.cpp \
    front/gridgui.cpp \
    front/mainwindow.cpp \
    main.cpp \
    front/gameview.cpp \
    front/targetgui.cpp \
    front/gamegui.cpp \
    front/gamesolngui.cpp

FORMS += \
    front/mainwindow.ui
