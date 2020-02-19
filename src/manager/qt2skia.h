/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

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

   Base on https://github.com/telishev/sneakPic/blob/master/src/renderer/qt2skia.h

**************************************************************************************/

#ifndef QT2SKIA_H
#define QT2SKIA_H


struct SkPoint;
class SkPath;

class QPointF;
class QPainterPath;

namespace skia{
  SkPoint skPoint (const QPointF &point);
  SkPath skPath (const QPainterPath &qpath);
  int skFillRule (int rule);
};

#endif // QT2SKIA_H
