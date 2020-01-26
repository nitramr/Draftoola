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

#ifndef ITEMEFFECTS_H
#define ITEMEFFECTS_H

#include <QGraphicsEffect>
#include <shadow.h>
#include <fills.h>

class ItemEffects : public QGraphicsEffect
{
public:
    ItemEffects(QObject *parent = nullptr);
	QRectF boundingRectFor(const QRectF &rect) const;

	void setShadowList(QList<Shadow> shadowList);
	void setFillsList(QList<Fills> fillsList);
	void setShape(QPainterPath shape);
	void setBlurRadius(qreal radius);

protected:
	void draw(QPainter *painter) override;
	void drawShadow(Shadow shadow, QPainter *p, const QPointF &pos, const QPixmap &px, bool isInnerShadow = false) const;
	void drawBlur(QPainter *p, const QPointF &pos, const QPixmap &px) const;
	void drawFills(Fills fills, QPainter *p) const;



private:
	qreal m_shadowRadius;
	qreal m_blurRadius;

	QList<Shadow> m_shadowList;
	QList<Fills> m_fillsList;
	QPainterPath m_shape;

};

#endif // ITEMEFFECTS_H
