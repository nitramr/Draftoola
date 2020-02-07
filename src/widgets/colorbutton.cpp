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

    QPainter painter(&iconPixmap);

    QPainterPath path;
    path.addRect(iconPixmap.rect());

    paintGrid(painter, path, QSize(6,6));
    painter.drawPixmap(pixmap.rect(), pixmap);

    QIcon icon(iconPixmap);
    QToolButton::setIcon(icon);
}

void ColorButton::setIcon(const QIcon &icon)
{
    QToolButton::setIcon(icon);
}

void ColorButton::setMenu(QMenu *menu)
{
    QToolButton::setMenu(menu);
    connect(this->menu(), &QMenu::aboutToShow, this, &ColorButton::openPopup);
}
