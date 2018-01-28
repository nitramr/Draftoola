#ifndef WAOVAL_H
#define WAOVAL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>


#include "itembase.h"

class WAOval : public QGraphicsEllipseItem, public ItemBase
{
public:
	WAOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	WAOval(qreal width, qreal height, QGraphicsItem * parent = 0);
	WAOval(QRectF rect, QGraphicsItem * parent = 0);
	WAOval(QGraphicsItem * parent = 0);

	// Properties
	QPainterPath shape() const override;
	virtual QPainterPath shapeStroke(Stroke stroke) const;
//	virtual QRectF adjustedRect(StrokePosition strokePosition) const;

	// Events
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

};

#endif // WARECT_H
