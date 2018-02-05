#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>
#include <QImage>

#include "itemstruct.h"
#include "stroke.h"
#include "fills.h"
#include "gradient.h"
#include "shadow.h"

class ItemBase : public QGraphicsObject
{

public:

	ItemBase(QGraphicsItem *parent = 0);

    // Properties
    void setName(QString name);
    QString name() const;

    void setItemType(ItemType type);
    ItemType itemType() const;

	void addStroke(Stroke stroke);
	Stroke stroke(int id = 0) const;
	QList<Stroke> strokeList() const;

	void addFills(Fills fills);
	Fills fills(int id = 0) const;
	QList<Fills> fillsList() const;

	void addShadow(Shadow shadow);
	Shadow shadow(int id = 0) const;
	QList<Shadow> shadowList() const;

	void addInnerShadow(Shadow shadow);
	Shadow innerShadow(int id = 0) const;
	QList<Shadow> innerShadowList() const;

	void setScaleFactor(qreal scaleFactor);
	qreal scaleFactor() const;

//	virtual void setRect(QRectF rect);
//	virtual QRectF rect() const;

//	virtual QRectF boundingRect() const;

//	virtual void setShape(QPainterPath shape);
//	virtual QPainterPath shape() const;

//	QPointF anchorTopLeft() const;
//	QPointF anchorTop() const;
//	QPointF anchorTopRight() const;
//	QPointF anchorRight() const;
//	QPointF anchorBottomRight() const;
//	QPointF anchorBottom() const;
//	QPointF anchorBottomLeft() const;
//	QPointF anchorLeft() const;
//	QPointF anchorCenter() const;


	// Members
	void addExportFactor(QString key, double value);
	void removeExportFactor(QString key);

	QRectF drawShadow(Shadow shadow, QPainter *painter, QPainterPath shapeScaled);
	QRectF drawInnerShadow(Shadow shadow, QPainter *painter, QPainterPath clippingShape, QPainterPath shapeScaled, QPainterPath clippingShapeScaled);
	QRectF drawFills(Fills fills, QPainter *painter, QPainterPath shape);
	QRectF drawStrokes(Stroke stroke, QPainter *painter, QPainterPath shape);
	QRectF drawBlur(QRectF shapeRect, QPainter *painter, qreal radius);


private:
	// Properties
	QRectF m_rect;
	QRectF m_boundingRect;
	QPainterPath m_shape;
    QString m_name;
    ItemType m_itemType;
	StrokePosition m_strokePosition;
	qreal m_scaleFactor;

	// Members
	QMap<QString, double>	m_exportFactorList;
	QList<Fills>			m_fillsList;
	QList<Stroke>			m_strokeList;
	QList<Shadow>			m_shadowList;
	QList<Shadow>			m_innerShadowList;

//	void setShape();

};

#endif // ITEMBASE_H
