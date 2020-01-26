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

#ifndef ROUNDEDPOLYGON_H
#define ROUNDEDPOLYGON_H

#include <QPainterPath>

class RoundedPolygon : public QPolygonF
{
public:
    RoundedPolygon()
    {    SetRadius(10); }

    void SetRadius(unsigned int iRadius)
    {    m_iRadius = iRadius; }

    const QPainterPath& GetPath();

private:
    QPointF GetLineStart(int i) const;
    QPointF GetLineEnd(int i) const;
    float GetDistance(QPointF pt1, QPointF pt2) const;
private:
    QPainterPath m_path;
    unsigned int m_iRadius;
};

#endif // ROUNDEDPOLYGON_H
