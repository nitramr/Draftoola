#include "waoval.h"

#include <QtWidgets>

WAOval::WAOval(QGraphicsItem *parent) : WAOval(0,0,300,350, parent){}
WAOval::WAOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WAOval(QRectF(x,y,width,height), parent){}
WAOval::WAOval(qreal width, qreal height, QGraphicsItem *parent) : WAOval(QRectF(0,0,width,height), parent){}
WAOval::WAOval(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent){
	this->setItemType(ItemType::Oval);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/


/***************************************************
 *
 * Events
 *
 ***************************************************/

void WAOval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

	painter->setBrush(this->fills());
	painter->setPen(this->stroke());
	painter->drawEllipse(this->rectAdjusted());



}
