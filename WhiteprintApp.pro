#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T12:56:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhiteprintApp
TEMPLATE = app


SOURCES += whiteprint/main.cpp\
        whiteprint/mainwindow.cpp \
    whiteprint/designer/canvas.cpp \
    whiteprint/item/artboard.cpp \
    whiteprint/item/warect.cpp \
    whiteprint/designer/wascene.cpp \
    whiteprint/item/handleframe.cpp \
    whiteprint/item/itembase.cpp \
    whiteprint/item/stroke.cpp \
    whiteprint/item/fills.cpp \
    whiteprint/item/gradient.cpp

HEADERS  += whiteprint/mainwindow.h \
    whiteprint/designer/canvas.h \
    whiteprint/item/artboard.h \
    whiteprint/item/warect.h \
    whiteprint/designer/wascene.h \
    whiteprint/item/handleframe.h \
    whiteprint/item/itembase.h \
    whiteprint/item/itemstruct.h \
    whiteprint/item/stroke.h \
    whiteprint/item/fills.h \
    whiteprint/item/gradient.h

FORMS    += whiteprint/mainwindow.ui
