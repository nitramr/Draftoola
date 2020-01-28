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

#ifndef ITEMOVAL_H
#define ITEMOVAL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>

#include <itembase.h>

class ItemOval : public ItemBase
{
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QRect rect READ rect WRITE setRect)

public:
    ItemOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemOval(qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemOval(QRectF rect, QGraphicsItem * parent = nullptr);
    ItemOval(QGraphicsItem * parent = nullptr);
    ItemOval(const ItemOval &other);


    // operator
    bool operator==( const ItemOval & other ) const;
    inline bool operator!=(const ItemOval &itemBase) const;


	// Properties
    int type() const override { return Type::Oval; }
    void setRect(QRectF rect) override;

};

#endif // ITEMOVAL_H
