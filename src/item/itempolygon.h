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

#ifndef ITEMSTAR_H
#define ITEMSTAR_H

#include <itembase.h>

class ItemPolygon : public ItemBase
{
public:
    ItemPolygon(qreal x, qreal y, qreal width, qreal height, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(qreal width, qreal height, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(QRectF rect, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(QGraphicsItem * parent = nullptr);
    ItemPolygon(const ItemPolygon &other);


    // operator
    bool operator==( const ItemPolygon & other ) const;
    inline bool operator!=(const ItemPolygon &itemBase) const;


    // Properties
    int type() const override { return Type::Polygon; }
    void setSides(int count);
    int sides() const;
    void setInnerRadius(qreal length);
    qreal innerRadius() const;
    void setUseInnerRadius(bool allow);
    bool useInnerRadius();

    void setRect(QRectF rect) override;
    virtual QPainterPath shapeScaled(QRectF frame) const;

private:
    int m_sides;
    qreal m_innerRadius;
    bool m_useInnerRadius;

};

#endif // ITEMSTAR_H
