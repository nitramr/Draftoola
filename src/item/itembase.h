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

#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>
#include <QImage>
#include <QPixmapCache>

#include <utilities.h>
#include <stroke.h>
#include <fills.h>
#include <gradient.h>
#include <shadow.h>
#include <abstractitembase.h>
#include <SkPath.h>

class ItemBase : public AbstractItemBase
{

public:

    ItemBase(const QRectF rect, QGraphicsItem *parent = nullptr);
//    ItemBase(const ItemBase &other);
    ItemBase(const ItemBase &) = default;

    // operator
    bool operator==( const ItemBase & other ) const;
    inline bool operator!=(const ItemBase &itemBase) const;


    // Properties
	void addStroke(Stroke stroke);
    void updateStroke(Stroke stroke);
    void removeStroke(Stroke stroke);
	Stroke stroke(int id = 0) const;    
	QList<Stroke> strokeList() const;
    bool hasStrokes() const;

	void addFills(Fills fills);
    void updateFills(Fills fills);
    void removeFills(Fills fills);
	Fills fills(int id = 0) const;    
    QList<Fills> fillsList() const;
    bool hasFills() const;

	void addShadow(Shadow shadow);
    void updateShadow(Shadow shadow);
    void removeShadow(Shadow shadow);
	Shadow shadow(int id = 0) const;    
	QList<Shadow> shadowList() const;
    bool hasShadows() const;

	void addInnerShadow(Shadow shadow);
    void updateInnerShadow(Shadow shadow);
    void removeInnerShadow(Shadow shadow);
	Shadow innerShadow(int id = 0) const;    
	QList<Shadow> innerShadowList() const;
    bool hasInnerShadows() const;

    virtual void setRect(QRectF rect) override = 0;
    QRectF renderRect() const override;

    void clipsChildrenToShape(bool doClip);


	// Members
    QPainterPath scaleStroke(const QPainterPath & path, qreal amount , QPen pen = QPen()) const;

    void addItem(AbstractItemBase *item) override;
    void calculateRenderRect();

    // Events
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
	// Properties
    Stroke::StrokePosition m_strokePosition;
    SkPath m_shadowPath;
    QRectF m_renderRect;

    // Members
    QList<Fills>                m_fillsList;
    QList<Stroke>               m_strokeList;
    QList<Shadow>               m_shadowList;
    QList<Shadow>               m_innerShadowList;
    QMap<QString,QPainterPath>  m_shadowPathList;
    QMap<QString,QPainterPath>  m_innerShadowPathList;
    SkPath                      m_skshape;

    bool m_hasFills;
    bool m_hasStrokes;
    bool m_hasInnerShadows;
    bool m_hasShadows;


    qreal lod();
    SkPath strokeShape() const;

    SkPath skshape() const;

    // functions    
    QImage blurShadow(QPainterPath shape, QSize size, qreal radius, qreal lod, QPainter::CompositionMode compositionMode, QColor tintColor = Qt::black) const;

    QRectF drawShadow(Shadow shadow, QPainter *painter);
    QRectF drawInnerShadow(Shadow shadow, QPainter *painter);
    QRectF drawFills(Fills fills, QPainter *painter);
    QRectF drawStrokes(Stroke stroke, QPainter *painter);
    QRectF drawBlur(qreal radius, QPainter *painter);

    QRectF calculateShadowPaths();
    void calculateInnerShadowPaths();

};

#endif // ITEMBASE_H
