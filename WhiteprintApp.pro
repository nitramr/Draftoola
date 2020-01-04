#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T12:56:24
#
#-------------------------------------------------

QT += core gui widgets svg
#QT += gui-private # add private classes
QT += script
#qtHaveModule(printsupport): QT += printsupport

#CONFIG += c++14

TARGET = WhiteprintApp
TEMPLATE = app

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/designer/canvasscene.cpp \
    src/designer/canvasview.cpp \
    src/designer/handleframe.cpp \
    src/designer/ruler.cpp \
    src/item/abstractitembase.cpp \
    src/item/artboard.cpp \
    src/item/exportlevel.cpp \
    src/item/fills.cpp \
    src/item/gradient.cpp \
    src/item/itembase.cpp \
    src/item/itemeffects.cpp \
    src/item/itemtext.cpp \
    src/item/itemrect.cpp \
    src/item/itemoval.cpp \
    src/item/itemgroup.cpp \
    src/item/shadow.cpp \
    src/item/stroke.cpp \
    src/item/path/pathhandler.cpp \
    src/item/path/roundedpolygon.cpp \
    src/manager/stylefactory.cpp \
    src/widgets/buttongroup.cpp \
    src/widgets/colorbutton.cpp \
    src/widgets/flowlayout.cpp \
    src/widgets/intelligentspinbox.cpp \
    src/widgets/layoutsection.cpp \
    src/widgets/popupmenu.cpp \
    src/workspace/tool_itemproperties.cpp \
    src/workspace/tool_outliner.cpp \
    src/workspace/components/propertyexportlevel.cpp \
    src/workspace/components/propertyfill.cpp \
    src/workspace/components/propertyshadow.cpp \
    src/workspace/components/propertystroke.cpp \
    src/workspace/tool_itemproperties/ip_geometry.cpp \
    src/workspace/tool_itemproperties/ip_fills.cpp \
    src/workspace/tool_itemproperties/ip_exportlevel.cpp \
    src/workspace/tool_itemproperties/ip_shadows.cpp \
    src/workspace/tool_itemproperties/ip_strokes.cpp \
    src/item/abstractitemproperty.cpp \
    src/workspace/tool_itemproperties/ip_innershadows.cpp

HEADERS  +=     src/mainwindow.h \
    src/designer/canvasscene.h \
    src/designer/canvasview.h \
    src/designer/handleframe.h \
    src/designer/ruler.h \
    src/item/abstractitembase.h \
    src/item/artboard.h \
    src/item/exportlevel.h \
    src/item/fills.h \
    src/item/gradient.h \
    src/item/itembase.h \
    src/item/itemeffects.h \
    src/item/itemtext.h \
    src/item/itemrect.h \
    src/item/itemoval.h \
    src/item/itemgroup.h \
    src/item/itemstruct.h \
    src/item/shadow.h \
    src/item/stroke.h \
    src/item/path/pathhandler.h \
    src/item/path/roundedpolygon.h \
    src/manager/stylefactory.h \
    src/widgets/buttongroup.h \
    src/widgets/colorbutton.h \
    src/widgets/flowlayout.h \
    src/widgets/intelligentspinbox.h \
    src/widgets/layoutsection.h \
    src/widgets/popupmenu.h \
    src/workspace/tool_itemproperties.h \
    src/workspace/tool_outliner.h \
    src/workspace/components/propertyexportlevel.h \
    src/workspace/components/propertyfill.h \
    src/workspace/components/propertyshadow.h \
    src/workspace/components/propertystroke.h \
    src/workspace/tool_itemproperties/ip_geometry.h \
    src/workspace/tool_itemproperties/ip_fills.h \
    src/workspace/tool_itemproperties/ip_exportlevel.h \
    src/workspace/tool_itemproperties/ip_shadows.h \
    src/workspace/tool_itemproperties/ip_strokes.h \
    src/item/abstractitemproperty.h \
    src/workspace/tool_itemproperties/ip_innershadows.h

FORMS    += src/mainwindow.ui \
    src/workspace/tool_itemproperties.ui \
    src/workspace/tool_outliner.ui \
    src/workspace/components/propertyfill.ui \
    src/workspace/components/propertystroke.ui \
    src/workspace/components/propertyexportlevel.ui \
    src/workspace/components/propertyshadow.ui \
    src/workspace/tool_itemproperties/ip_exportlevel.ui \
    src/workspace/tool_itemproperties/ip_fills.ui \
    src/workspace/tool_itemproperties/ip_geometry.ui \
    src/workspace/tool_itemproperties/ip_shadows.ui \
    src/workspace/tool_itemproperties/ip_strokes.ui

RESOURCES += \
    src/resources/icons/icons.qrc
