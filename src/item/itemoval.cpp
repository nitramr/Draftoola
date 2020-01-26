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

#include <itemoval.h>

ItemOval::ItemOval(QGraphicsItem *parent) : ItemOval(0,0,80,80, parent){}
ItemOval::ItemOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(x,y,width,height), parent){}
ItemOval::ItemOval(qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(0,0,width,height), parent){}
ItemOval::ItemOval(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent){

    this->setRect(rect);
    this->setName(tr("Oval"));

}

ItemOval::ItemOval(const ItemOval &other) : ItemBase(other){}

bool ItemOval::operator==(const ItemOval &other) const
{
    if(this == &other) return true;

    return ItemBase::operator==(other);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemOval::setRect(QRectF rect)
{
    switch(frameType()){
    case AbstractItemBase::FixedWidth:
        rect.setWidth(this->rect().width());
        break;
    case AbstractItemBase::FixedHeight:
        rect.setHeight(this->rect().height());
        break;
    case AbstractItemBase::FixedSize:
        rect = this->rect();
        break;
     case AbstractItemBase::Free:
        break;
    }

    QPainterPath path;
    path.addEllipse(rect);
    ItemBase::setShape(path);
    calculateRenderRect();
}

