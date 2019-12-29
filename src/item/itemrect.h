#ifndef ITEMRECT_H
#define ITEMRECT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>


#include "itembase.h"

class ItemRect : public ItemBase
{

public:
    ItemRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemRect(qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemRect(QRectF rect, QGraphicsItem * parent = nullptr);
    ItemRect(QGraphicsItem * parent = nullptr);

	// Properties
	void setRadius(qreal radius);
	void setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft);
	qreal radius() const;
    void setRect(QRectF rect);
    virtual QPainterPath shapeScaled(QRectF frame) const;
//    virtual QPainterPath shapeScaled2(QRectF frame, qreal scaleFactor, qreal offset = 0, Stroke stroke = Stroke("tmp",QBrush(Qt::transparent),0, StrokePosition::Center)) const;

private:

	qreal m_radiusTL;
	qreal m_radiusTR;
	qreal m_radiusBR;
	qreal m_radiusBL;
};

#endif // WARECT_H
