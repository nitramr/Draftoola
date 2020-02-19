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

**************************************************************************************/

#include "qt2skia.h"

#include <utilities.h>

#include <QPointF>
#include <QPainterPath>

#include <skia_includes.h>

namespace skia{


SkPoint skPoint (const QPointF &point)
{
  return SkPoint::Make(SkFloatToScalar (point.x ()), SkFloatToScalar (point.y ()));
}

int skFillRule (int rule)
{
  switch(rule)
    {
    case Qt::FillRule::OddEvenFill:
      return (int)SkPathFillType::kEvenOdd;
    case Qt::FillRule::WindingFill:
  default:
      return (int)SkPathFillType::kWinding ;
    }
}

SkPath skPath (const QPainterPath &qpath)
{
  SkPath path;
  int count = qpath.elementCount();
  for(int i = 0; i < count; i++)
    {
      QPainterPath::Element elem = qpath.elementAt(i);
      switch(elem.type)
        {
        case QPainterPath::MoveToElement:
          path.moveTo(skPoint(elem));
          break;
        case QPainterPath::LineToElement:
          path.lineTo(skPoint(elem));
          break;
        case QPainterPath::CurveToElement:
          {
            path.cubicTo(skPoint(elem),
                         skPoint(qpath.elementAt(i+1)),
                         skPoint(qpath.elementAt(i+2))
                         );
            break;
          }
        default:
          break;
        }
    }

  if(count == 1)
    {
      path.lineTo( skPoint( qpath.elementAt(0) ));
      path.close();
    }

  if(count > 3
         && are_equal( qpath.elementAt(count - 1).x, qpath.elementAt(0).x )
         && are_equal( qpath.elementAt(count - 1).y, qpath.elementAt(0).y )
     )
    path.close();
  // Qt doesn't have any special definition if path is closed expect that it's first and last points are equal

  path.setFillType( (SkPathFillType)skFillRule( qpath.fillRule() ));
  return path;
}



};
