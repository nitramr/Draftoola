#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T12:56:24
#
#-------------------------------------------------

QT += core gui widgets svg designer opengl
#QT += gui-private # add private classes
QT += script
#qtHaveModule(printsupport): QT += printsupport

include (skia.pri)

CONFIG += c++17

TARGET = Draftoola
TEMPLATE = app

SOURCES += \
    src/designer/canvasscene.cpp \
    src/designer/canvasview.cpp \
    src/designer/handleframe.cpp \
    src/designer/ruler.cpp \
    src/gui/colordialog/QtColorWidgets/color_2d_slider.cpp \
    src/gui/colordialog/QtColorWidgets/color_line_edit.cpp \
    src/gui/colordialog/QtColorWidgets/color_names.cpp \
    src/gui/colordialog/QtColorWidgets/color_preview.cpp \
    src/gui/colordialog/QtColorWidgets/gradient_editor.cpp \
    src/gui/colordialog/QtColorWidgets/gradient_slider.cpp \
    src/gui/colordialog/QtColorWidgets/hue_slider.cpp \
    src/gui/colordialog/colordialog.cpp \
    src/gui/colordialog/colorinput.cpp \
    src/gui/colordialog/tabcolors.cpp \
    src/gui/colordialog/tabimage.cpp \
    src/gui/tool_itemproperties.cpp \
    src/gui/tool_itemproperties/ip_exportlevel.cpp \
    src/gui/tool_itemproperties/ip_fills.cpp \
    src/gui/tool_itemproperties/ip_geometry.cpp \
    src/gui/tool_itemproperties/ip_innershadows.cpp \
    src/gui/tool_itemproperties/ip_shadows.cpp \
    src/gui/tool_itemproperties/ip_strokes.cpp \
    src/gui/tool_itemproperties/propertyexportlevel.cpp \
    src/gui/tool_itemproperties/propertyfill.cpp \
    src/gui/tool_itemproperties/propertyshadow.cpp \
    src/gui/tool_itemproperties/propertystroke.cpp \
    src/gui/tool_outliner.cpp \
    src/gui/widgets/buttongroup.cpp \
    src/gui/widgets/colorbutton.cpp \
    src/gui/widgets/flowlayout.cpp \
    src/gui/widgets/intelligentspinbox.cpp \
    src/gui/widgets/layoutsection.cpp \
    src/gui/widgets/popupmenu.cpp \
    src/item/abstractitembase.cpp \
    src/item/artboard.cpp \
    src/item/itembase.cpp \
    src/item/itemgroup.cpp \
    src/item/itemoval.cpp \
    src/item/itempolygon.cpp \
    src/item/itemrect.cpp \
    src/item/itemtext.cpp \
    src/item/members/abstractitemproperty.cpp \
    src/item/members/abstractproperty.cpp \
    src/item/members/color.cpp \
    src/item/members/exportlevel.cpp \
    src/item/members/fills.cpp \
    src/item/members/gradient.cpp \
    src/item/members/pathprocessor.cpp \
    src/item/members/shadow.cpp \
    src/item/members/stroke.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/manager/qt2skia.cpp \
    src/manager/skia2qt.cpp \
    src/manager/stylefactory.cpp

HEADERS  += \
    src/common/skia_includes.h \
    src/common/utilities.h \
    src/designer/canvasscene.h \
    src/designer/canvasview.h \
    src/designer/handleframe.h \
    src/designer/ruler.h \
    src/gui/colordialog/QtColorWidgets/color_2d_slider.hpp \
    src/gui/colordialog/QtColorWidgets/color_line_edit.hpp \
    src/gui/colordialog/QtColorWidgets/color_names.hpp \
    src/gui/colordialog/QtColorWidgets/color_preview.hpp \
    src/gui/colordialog/QtColorWidgets/color_utils.hpp \
    src/gui/colordialog/QtColorWidgets/colorwidgets_global.hpp \
    src/gui/colordialog/QtColorWidgets/gradient_editor.hpp \
    src/gui/colordialog/QtColorWidgets/gradient_helper.hpp \
    src/gui/colordialog/QtColorWidgets/gradient_slider.hpp \
    src/gui/colordialog/QtColorWidgets/hue_slider.hpp \
    src/gui/colordialog/colordialog.h \
    src/gui/colordialog/colorinput.h \
    src/gui/colordialog/tabcolors.h \
    src/gui/colordialog/tabimage.h \
    src/gui/tool_itemproperties.h \
    src/gui/tool_itemproperties/ip_exportlevel.h \
    src/gui/tool_itemproperties/ip_fills.h \
    src/gui/tool_itemproperties/ip_geometry.h \
    src/gui/tool_itemproperties/ip_innershadows.h \
    src/gui/tool_itemproperties/ip_shadows.h \
    src/gui/tool_itemproperties/ip_strokes.h \
    src/gui/tool_itemproperties/propertyexportlevel.h \
    src/gui/tool_itemproperties/propertyfill.h \
    src/gui/tool_itemproperties/propertyshadow.h \
    src/gui/tool_itemproperties/propertystroke.h \
    src/gui/tool_outliner.h \
    src/gui/widgets/buttongroup.h \
    src/gui/widgets/colorbutton.h \
    src/gui/widgets/flowlayout.h \
    src/gui/widgets/intelligentspinbox.h \
    src/gui/widgets/layoutsection.h \
    src/gui/widgets/layoutsegment.h \
    src/gui/widgets/popupmenu.h \
    src/item/abstractitembase.h \
    src/item/artboard.h \
    src/item/itembase.h \
    src/item/itemgroup.h \
    src/item/itemoval.h \
    src/item/itempolygon.h \
    src/item/itemrect.h \
    src/item/itemtext.h \
    src/item/members/abstractitemproperty.h \
    src/item/members/abstractproperty.h \
    src/item/members/color.h \
    src/item/members/exportlevel.h \
    src/item/members/fills.h \
    src/item/members/gradient.h \
    src/item/members/pathprocessor.h \
    src/item/members/shadow.h \
    src/item/members/stroke.h \
    src/mainwindow.h \
    src/manager/qt2skia.h \
    src/manager/skia2qt.h \
    src/manager/stylefactory.h

FORMS    += \
    src/gui/colordialog/colordialog.ui \
    src/gui/colordialog/colorinput.ui \
    src/gui/colordialog/tabcolors.ui \
    src/gui/colordialog/tabimage.ui \
    src/gui/tool_itemproperties.ui \
    src/gui/tool_itemproperties/ip_exportlevel.ui \
    src/gui/tool_itemproperties/ip_fills.ui \
    src/gui/tool_itemproperties/ip_geometry.ui \
    src/gui/tool_itemproperties/ip_shadows.ui \
    src/gui/tool_itemproperties/ip_strokes.ui \
    src/gui/tool_itemproperties/propertyexportlevel.ui \
    src/gui/tool_itemproperties/propertyfill.ui \
    src/gui/tool_itemproperties/propertyshadow.ui \
    src/gui/tool_itemproperties/propertystroke.ui \
    src/gui/tool_outliner.ui \
    src/mainwindow.ui

RESOURCES += \
    src/resources/icons/icons.qrc

INCLUDEPATH += \
    $$PWD/src \
    $$PWD/src/common \    
    $$PWD/src/designer \
    $$PWD/src/gui \
    $$PWD/src/gui/colordialog \
    $$PWD/src/gui/colordialog/QtColorWidgets \    
    $$PWD/src/gui/tool_itemproperties \
    $$PWD/src/gui/widgets \
    $$PWD/src/item \
    $$PWD/src/item/members \
    $$PWD/src/manager
