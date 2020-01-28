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

#ifndef ITEMRECT_H
#define ITEMRECT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>

#include <itembase.h>

class ItemRect : public ItemBase
{

    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QRect rect READ rect WRITE setRect)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)

public:
    ItemRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemRect(qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemRect(QRectF rect, QGraphicsItem * parent = nullptr);
    ItemRect(QGraphicsItem * parent = nullptr);
    ItemRect(const ItemRect &other);


    // operator
    bool operator==( const ItemRect & other ) const;
    inline bool operator!=(const ItemRect &itemBase) const;


	// Properties
    int type() const override { return Type::Rect; }
	void setRadius(qreal radius);
	void setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft);
	qreal radius() const;
    void setRect(QRectF rect) override;
    virtual QPainterPath shapeScaled(QRectF frame) const;
//    virtual QPainterPath shapeScaled2(QRectF frame, qreal scaleFactor, qreal offset = 0, Stroke stroke = Stroke("tmp",QBrush(Qt::transparent),0, StrokePosition::Center)) const;

private:

	qreal m_radiusTL;
	qreal m_radiusTR;
	qreal m_radiusBR;
	qreal m_radiusBL;
};

#endif // WARECT_H
