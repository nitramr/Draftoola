#ifndef WARECT_H
#define WARECT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>


#include "itembase.h"

class WARect : public ItemBase
{

public:
	WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	WARect(qreal width, qreal height, QGraphicsItem * parent = 0);
    WARect(QRectF rect, QGraphicsItem * parent = 0);
    WARect(QGraphicsItem * parent = 0);

	// Properties
	void setRadius(qreal radius);
	void setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft);
	qreal radius() const;
	virtual void setRect(QRectF rect);
	virtual QRectF rect() const;
	virtual QPainterPath shape() const;
	virtual QPainterPath shapeScaled(qreal scaleFactor, qreal offset = 0, Stroke stroke = Stroke("tmp",QBrush(Qt::transparent),0, StrokePosition::Center)) const;
	virtual QPainterPath shapeStroke(Stroke stroke) const;
	virtual QRectF boundingRect() const;
//	QPointF anchorTopLeft() const;
//	QPointF anchorTop() const;
//	QPointF anchorTopRight() const;
//	QPointF anchorRight() const;
//	QPointF anchorBottomRight() const;
//	QPointF anchorBottom() const;
//	QPointF anchorBottomLeft() const;
//	QPointF anchorLeft() const;
//	QPointF anchorCenter() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

	qreal m_radiusTL;
	qreal m_radiusTR;
	qreal m_radiusBR;
	qreal m_radiusBL;

	QRectF m_boundingRect;
	QRectF m_rect;

};

#endif // WARECT_H
