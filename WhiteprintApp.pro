#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T12:56:24
#
#-------------------------------------------------

QT += core gui widgets
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhiteprintApp
TEMPLATE = app
#LIBS += -framework CoreFoundation


SOURCES += whiteprint/main.cpp\
    whiteprint/mainwindow.cpp \
    whiteprint/designer/canvas.cpp \
    whiteprint/item/artboard.cpp \
    whiteprint/item/warect.cpp \
    whiteprint/designer/wascene.cpp \
    whiteprint/designer/handleframe.cpp \
    whiteprint/item/itembase.cpp \
    whiteprint/item/stroke.cpp \
    whiteprint/item/fills.cpp \
    whiteprint/item/gradient.cpp \
    whiteprint/item/waoval.cpp \
    whiteprint/designer/waview.cpp \
    whiteprint/designer/canvasframe.cpp \
    whiteprint/item/watext.cpp \
    whiteprint/workspace/tool_itemproperties.cpp \
    whiteprint/workspace/tool_outliner.cpp \
    whiteprint/item/wagroup.cpp \
    whiteprint/item/itemeffects.cpp \
    whiteprint/item/shadow.cpp

HEADERS  += whiteprint/mainwindow.h \
    whiteprint/designer/canvas.h \
    whiteprint/item/artboard.h \
    whiteprint/item/warect.h \
    whiteprint/designer/wascene.h \
    whiteprint/designer/handleframe.h \
    whiteprint/item/itembase.h \
    whiteprint/item/itemstruct.h \
    whiteprint/item/stroke.h \
    whiteprint/item/fills.h \
    whiteprint/item/gradient.h \
    whiteprint/item/waoval.h \
    whiteprint/designer/waview.h \
    whiteprint/designer/canvasframe.h \
    whiteprint/item/watext.h \
    whiteprint/workspace/tool_outliner.h \
    whiteprint/workspace/tool_itemproperties.h \
    whiteprint/item/wagroup.h \
    whiteprint/item/itemeffects.h \
    whiteprint/item/shadow.h

FORMS    += whiteprint/mainwindow.ui \
    whiteprint/workspace/tool_itemproperties.ui \
    whiteprint/workspace/tool_outliner.ui
