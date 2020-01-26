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

#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QGraphicsItemGroup>

#include <abstractitembase.h>

class ItemGroup : public AbstractItemBase
{

public:
    explicit ItemGroup(QGraphicsItem *parent = nullptr);

	// Properties
    int type() const override { return Type::Group; }
    void setRect(QRectF rect) override;
    QRectF renderRect() const override;
    QRectF rect() const override;
    QRectF boundingRect() const override;


    // Member
    void addItem(AbstractItemBase *childItems) override;
    QList<AbstractItemBase*> childItems() const override;


    // Events
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void render(QPainter *painter) override;

private:
    QList<AbstractItemBase*> m_children;
    QRectF m_renderRect;
    QRectF m_rect;

signals:

public slots:
};

#endif // WAGROUP_H
