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

#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H

#include <QMetaType>
#include <QPainter>
#include <QDebug>

enum class FillType {
    Color = 0,
    Image = 1,
    LinearGradient = 2,
    RadialGradient = 3,
    ConicalGradient = 4,
    Pattern = 5

};
Q_DECLARE_METATYPE(FillType)


inline void paintGrid(QPainter &painter, QPainterPath path, QSize grid){

    int xP = path.boundingRect().x(), yP = path.boundingRect().y(), offset = 0, gridX = grid.width(), gridY = grid.height();
    QSize count( path.boundingRect().width() / gridX, path.boundingRect().height() / gridY);

    painter.save();
    painter.setClipPath(path);
    painter.fillPath(path, Qt::white);

    for(int r = 0;  r <= count.height(); r++)
    {
        for(int c = 0; c <= count.width(); c++)
        {
            if(offset == 0)
            {
                painter.fillRect(QRect( xP, yP, gridX, gridY ), Qt::lightGray);
                offset++;
            }
            else offset--;
            xP += gridX;
        }
        xP = path.boundingRect().x();
        yP += gridY;
        offset = (r % 2) ? 0 : 1;
    }
    painter.restore();
}


#endif // ITEMSTRUCT_H
