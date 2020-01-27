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

#include "colorbutton.h"
#include <QPainter>
#include <QDebug>
#include <utilities.h>

ColorButton::ColorButton(QWidget *parent) : QToolButton(parent)
{
    setPopupMode(QToolButton::InstantPopup);
    setStyleSheet("QToolButton::menu-indicator { image: none; }");
}

void ColorButton::setIcon(const QPixmap &pixmap)
{

    QPixmap iconPixmap(pixmap.size());
    iconPixmap.fill(Qt::white);

    QPainter painter(&iconPixmap);
//    painter.setPen(Qt::NoPen);

//    int x = 0, y = 0, offset = 0, grid = 6;
//    QSize count( pixmap.width() / grid, pixmap.height() / grid);

//    for(int l = 0;  l <= count.height(); l++)
//    {
//        for(int r = 0; r <= count.width(); r++)
//        {
//            if(offset == 0)
//            {
//                painter.fillRect(QRect( x, y, grid, grid ), Qt::lightGray);
//                offset++;
//            }
//            else offset--;
//            x += grid;
//        }
//        x = 0;
//        y += grid;
//        offset = (offset == 0) ? 1 : 0;
//    }

    paintGrid(painter, iconPixmap.rect(), QSize(6,6));

    painter.drawPixmap(pixmap.rect(), pixmap);

    QIcon icon(iconPixmap);

    QToolButton::setIcon(icon);
}

void ColorButton::setIcon(const QIcon &icon)
{
    QToolButton::setIcon(icon);
}
