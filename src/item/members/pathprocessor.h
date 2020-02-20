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

#ifndef PATHHANDLER_H
#define PATHHANDLER_H

#include <QPainterPath>
#include <QTransform>
#include <skia_includes.h>

class PathProcessor
{
public:
    enum class Booleans {
        Unite = 0,
        Subtract = 1,
        Intersect = 2,
        InvertIntersect = 3
    };

    static QPainterPath combine(const QPainterPath &path1, const QPainterPath &path2, Booleans boolOperator = Booleans::Unite);
    static SkPath combine(const SkPath &path1, const SkPath &path2, Booleans boolOperator = Booleans::Unite);

    static QPainterPath scale( const QPainterPath &path, qreal amount);

    static QPainterPath simplify(QPainterPath path);
    static SkPath simplify(SkPath path);

    static QPainterPath map(QTransform transform, QPainterPath sourcePath);
    static SkPath map(SkMatrix matrix, SkPath sourcePath);

};

#endif // PATHHANDLER_H
