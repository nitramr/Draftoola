#include "warect.h"

#include <QtWidgets>

WARect::WARect(QGraphicsItem *parent) : WARect(0,0,300,350, parent){}
WARect::WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(x,y,width,height), parent){}
WARect::WARect(qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(0,0,width,height), parent){}
WARect::WARect(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent), m_radius(0){
    this->setItemType(ItemType::Rect);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void WARect::setRadius(qreal radius)
{
	m_radius = radius;
}

qreal WARect::radius() const
{
	return m_radius;
}

/***************************************************
 *
 * Events
 *
 ***************************************************/

void WARect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
    Q_UNUSED(widget);

//	painter->setClipRect( option->exposedRect );

	painter->setBrush(this->fills());
	painter->setPen(this->stroke());
	painter->drawRoundedRect(this->adjustedRect(), m_radius, m_radius);


}
