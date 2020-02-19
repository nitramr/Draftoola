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

#include "skia2qt.h"

#include <QTransform>
#include <QPointF>
#include <QPainterPath>
#include <QRect>
#include <QRectF>
#include <QDebug>

#include "skia_includes.h"

namespace skia{

int qtFillRule (int rule)
{
  switch (SkPathFillType(rule))
    {
    case SkPathFillType::kEvenOdd:
      return Qt::FillRule::OddEvenFill;
    case SkPathFillType::kWinding:
    default:
      return Qt::FillRule::WindingFill;
    }
}

QPointF qtPoint (const SkPoint &skpoint)
{
    return QPointF(skpoint.x(), skpoint.y());
}

QPainterPath qtPath(const SkPath &skpath)
{
    QPainterPath path;
    int max = skpath.countVerbs();
    uint8_t verbs[max];
    skpath.getVerbs(verbs, max);

    int count = 0;

    for (int i = 0; i < max; ++i) {

        switch( verbs[i] ){
        case 0: // move 1
            path.moveTo(qtPoint(skpath.getPoint(count)));
            count +=1;
            break;
        case 1: // line 2
            path.lineTo(qtPoint(skpath.getPoint(count)));
            count +=1;
            break;
        case 2: // quad 3
            path.quadTo(
                        qtPoint(skpath.getPoint(count)),
                        qtPoint(skpath.getPoint(count+1))
                        );
            count +=2;
            break;
        case 3: // conic 4
            qDebug() << "conicTo" + QString::number(i);
            count +=3;
            break;
        case 4: // cubic 4
            path.cubicTo(
                        qtPoint(skpath.getPoint(count)),
                        qtPoint(skpath.getPoint(count+1)),
                        qtPoint(skpath.getPoint(count+2))
                        );
            count +=3;
            break;
        case 5: // close 1
        case 6: // done 0
            break;
        }
    }


    //    if (count == 1)
    //      {
    //        path.lineTo (skPoint (qpath.elementAt (0)));
    //        path.close ();
    //      }

    //    if (   count > 3
    //           && are_equal (qpath.elementAt (count - 1).x, qpath.elementAt (0).x)
    //           && are_equal (qpath.elementAt (count - 1).y, qpath.elementAt (0).y)
    //       )
    //      path.close ();

    path.setFillRule( (Qt::FillRule)qtFillRule((int)skpath.getFillType()) );
    return path;
}


};
