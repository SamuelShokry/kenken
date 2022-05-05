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
    back/backtracking.h \
    back/backtrackingfch.h \
    back/backtrackingfchac.h \
    back/cage.h \
    back/cell.h \
    back/draw.h \
    back/grid.h \
    back/kenken.h \
    back/operationsCategory.h \
    back/solver.h \
    front/cagebordersgui.h \
    front/framegui.h \
    front/mainwindow.h \
    front/gridgui.h \
    front/gameview.h \
    front/targetgui.h \
    front/gamegui.h \
    front/gamesolngui.h \
    back/kenkenwriter.h \
    back/kenkenreader.h

SOURCES += \
    back/backtracking.cpp \
    back/backtrackingfch.cpp \
    back/backtrackingfchac.cpp \
    back/cage.cpp \
    back/cell.cpp \
    back/draw.cpp \
    back/grid.cpp \
    back/kenken.cpp \
    back/operationsCategory.cpp \
    back/solver.cpp \
    front/cagebordersgui.cpp \
    front/framegui.cpp \
    front/gridgui.cpp \
    front/mainwindow.cpp \
    main.cpp \
    front/gameview.cpp \
    front/targetgui.cpp \
    front/gamegui.cpp \
    front/gamesolngui.cpp \
    back/kenkenwriter.cpp \
    back/kenkenreader.cpp

FORMS += \
    front/mainwindow.ui
