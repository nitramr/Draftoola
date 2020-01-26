/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2016 Bojan Kverh

   Widget based on code from https://www.toptal.com/c-plus-plus/rounded-corners-bezier-curves-qpainter

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

#include "roundedpolygon.h"
#include "math.h"

float RoundedPolygon::GetDistance(QPointF pt1, QPointF pt2) const
{
    float fD = (pt1.x() - pt2.x())*(pt1.x() - pt2.x()) +
         (pt1.y() - pt2.y()) * (pt1.y() - pt2.y());
    return sqrtf(fD);
}

QPointF RoundedPolygon::GetLineStart(int i) const
{
    QPointF pt;
    QPointF pt1 = at(i);
    QPointF pt2 = at((i+1) % count());
    float fRat = m_iRadius / GetDistance(pt1, pt2);
    if (fRat > 0.5f)
     fRat = 0.5f;

    pt.setX((1.0f-fRat)*pt1.x() + fRat*pt2.x());
    pt.setY((1.0f-fRat)*pt1.y() + fRat*pt2.y());
    return pt;
}

QPointF RoundedPolygon::GetLineEnd(int i) const
{
    QPointF pt;
    QPointF pt1 = at(i);
    QPointF pt2 = at((i+1) % count());
    float fRat = m_iRadius / GetDistance(pt1, pt2);
    if (fRat > 0.5f)
     fRat = 0.5f;
    pt.setX(fRat*pt1.x() + (1.0f - fRat)*pt2.x());
    pt.setY(fRat*pt1.y() + (1.0f - fRat)*pt2.y());
    return pt;
}

const QPainterPath& RoundedPolygon::GetPath()
{
    m_path = QPainterPath();

    if (count() < 3) {
     //qWarning() << "Polygon should have at least 3 points!";
     return m_path;
    }

    QPointF pt1;
    QPointF pt2;
    for (int i = 0; i < count(); i++) {
     pt1 = GetLineStart(i);

     if (i == 0)
         m_path.moveTo(pt1);
     else
         m_path.quadTo(at(i), pt1);

     pt2 = GetLineEnd(i);
     m_path.lineTo(pt2);
    }

    // close the last corner
    pt1 = GetLineStart(0);
    m_path.quadTo(at(0), pt1);

    return m_path;
}
