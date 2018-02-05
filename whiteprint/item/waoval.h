#ifndef WAOVAL_H
#define WAOVAL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>


#include "itembase.h"

class WAOval : public ItemBase
{
public:
	WAOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	WAOval(qreal width, qreal height, QGraphicsItem * parent = 0);
	WAOval(QRectF rect, QGraphicsItem * parent = 0);
	WAOval(QGraphicsItem * parent = 0);

	// Properties
	virtual QPainterPath shape() const;
	virtual QPainterPath shapeStroke(Stroke stroke) const;

	virtual void setRect(QRectF rect);
	virtual QRectF rect() const;

	virtual QRectF boundingRect() const;

	// Events
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

	QRectF m_rect;
	QRectF m_boundingRect;

};

#endif // WARECT_H
