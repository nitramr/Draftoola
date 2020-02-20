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

#include <math.h>

#define MINIMAL_FOR_COMPARISON 1e-6

static inline bool are_equal (double first, double second)
{
  return 3 * fabs (first - second) < (first + second + 1.0) * MINIMAL_FOR_COMPARISON;
}

static inline double cubed (double x) { return x * x * x; }
static inline double squared (double x) { return x * x; }

static inline QPixmap paintGrid(int blockSize = 6){

    QPixmap pixmap(blockSize*2,blockSize*2);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);

    painter.fillRect(QRect(blockSize,0,blockSize,blockSize), Qt::lightGray);
    painter.fillRect(QRect(0,blockSize,blockSize,blockSize), Qt::lightGray);

    return pixmap;
}



enum class FillType {
    Color = 0,
    Image = 1,
    LinearGradient = 2,
    RadialGradient = 3,
    ConicalGradient = 4,
    Pattern = 5

};
Q_DECLARE_METATYPE(FillType)


#endif // ITEMSTRUCT_H
