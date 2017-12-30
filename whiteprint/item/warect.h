#ifndef WARECT_H
#define WARECT_H

#include <QGraphicsItem>
#include <QDebug>


#include "whiteprint/item/itembase.h"

class WARect : public ItemBase
{
public:
	WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	WARect(qreal width, qreal height, QGraphicsItem * parent = 0);
    WARect(QRectF rect, QGraphicsItem * parent = 0);
    WARect(QGraphicsItem * parent = 0);

	// Properties
	void setRadius(qreal radius);
	qreal radius() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

	qreal m_radius;

};

#endif // WARECT_H
