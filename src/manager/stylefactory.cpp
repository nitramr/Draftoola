/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include <stylefactory.h>
#include <QtWidgets>

StyleFactory::StyleFactory(const QString name) : QProxyStyle(QStyleFactory::create(name))
{

}

void StyleFactory::drawControl(ControlElement control, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
//    case CE_PushButtonLabel:
//        {
//            QStyleOptionButton myButtonOption;
//            const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
//            if (buttonOption) {
//                myButtonOption = *buttonOption;
//                if (myButtonOption.palette.currentColorGroup()
//                        != QPalette::Disabled) {
//                    if (myButtonOption.state & (State_Sunken | State_On)) {
//                        myButtonOption.palette.setBrush(QPalette::ButtonText,
//                                myButtonOption.palette.brightText());
//                    }
//                }
//            }
//            QProxyStyle::drawControl(control, &myButtonOption, painter, widget);
//        }
//        break;
    default:
        QProxyStyle::drawControl(control, option, painter, widget);
    }
}

void StyleFactory::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
    case CC_ToolButton:
    {
        QStyleOptionToolButton myButtonOption;
        const QStyleOptionToolButton *buttonOption = qstyleoption_cast<const QStyleOptionToolButton *>(option);
        if (buttonOption) {
            myButtonOption = *buttonOption;
//            if (myButtonOption.palette.currentColorGroup() != QPalette::Disabled) {
//                if (myButtonOption.state & (State_Sunken | State_On)) {
//                    myButtonOption.palette.setBrush(QPalette::ButtonText,
//                            myButtonOption.palette.brightText());
//                }
//            }

        }

        QProxyStyle::drawComplexControl(control, &myButtonOption, painter, widget);
    }
        break;
    default:
        QProxyStyle::drawComplexControl(control, option, painter, widget);
    }
}
