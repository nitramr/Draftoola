/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2014 Alexey Telishev <telishev>
   Copyright (C) 2020 Martin Reininger <nitramr>

   Base on https://github.com/telishev/sneakPic/blob/master/src/renderer/qt2skia.cpp

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

#include <skia_includes.h>

namespace skia{

QTransform qtMatrix (const SkMatrix &tr)
{
  QTransform matrix;
  // scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2
  // m11, m21, m31, m12, m22, m32, m13, m23, m33
//  matrix.setMatrix(tr.getScaleX(), tr.getSkewX(), tr.getTranslateX(), tr.getSkewY(), tr.getScaleY(), tr.getTranslateY(), tr.getPerspX(), tr.getPerspY(), tr.get(8));
  matrix.setMatrix(tr.get(0), tr.get(1), tr.get(2), tr.get(3), tr.get(4), tr.get(5), tr.get(6), tr.get(7), tr.get(8));
  return matrix;
}


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
        case 0: // move
            path.moveTo(qtPoint(skpath.getPoint(count)));
            count +=1;
            break;
        case 1: // line
            path.lineTo(qtPoint(skpath.getPoint(count)));
            count +=1;
            break;
        case 2: // quad
            path.quadTo(
                        qtPoint(skpath.getPoint(count)),
                        qtPoint(skpath.getPoint(count+1))
                        );
            count +=2;
            break;
        case 3: // conic
            qDebug() << "conicTo";
            count +=3;
            break;
        case 4: // cubic
            path.cubicTo(
                        qtPoint(skpath.getPoint(count)),
                        qtPoint(skpath.getPoint(count+1)),
                        qtPoint(skpath.getPoint(count+2))
                        );
            count +=3;
            break;
        case 5: // close
        case 6: // done
            break;
        }
    }

    path.setFillRule( (Qt::FillRule)qtFillRule((int)skpath.getFillType()) );
    return path;
}


};
