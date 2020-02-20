/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2014 Alexey Telishev <telishev>
   Copyright (C) 2020 Martin Reininger <nitramr>

   Base on https://github.com/telishev/sneakPic/blob/master/src/renderer/qt2skia.h

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

#ifndef SKIA2QT_H
#define SKIA2QT_H

struct SkPoint;
class SkPath;
class SkMatrix;

class QPointF;
class QPainterPath;
class QTransform;

namespace skia{

    QTransform qtMatrix (const SkMatrix &tr);
    QPointF qtPoint (const SkPoint &skpoint);
    QPainterPath qtPath (const SkPath &skpath);
    int qtFillRule (int rule);

};

#endif // SKIA2QT_H
