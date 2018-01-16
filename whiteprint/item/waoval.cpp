#include "waoval.h"

#include <QtWidgets>

WAOval::WAOval(QGraphicsItem *parent) : WAOval(0,0,300,350, parent){}
WAOval::WAOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WAOval(QRectF(x,y,width,height), parent){}
WAOval::WAOval(qreal width, qreal height, QGraphicsItem *parent) : WAOval(QRectF(0,0,width,height), parent){}
WAOval::WAOval(QRectF rect, QGraphicsItem *parent) : QGraphicsEllipseItem(rect, parent){
	this->setItemType(ItemType::Oval);

	this->setFlags(QGraphicsItem::ItemIsSelectable |
				   QGraphicsItem::ItemIsFocusable |
				   QGraphicsItem::ItemClipsChildrenToShape |
				   QGraphicsItem::ItemContainsChildrenInShape |
				   QGraphicsItem::ItemSendsScenePositionChanges |
				   QGraphicsItem::ItemSendsGeometryChanges
				   );
	this->setAcceptHoverEvents(true);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/
QPainterPath WAOval::shape() const
{
	QPainterPath path;
	path.addEllipse(adjustedRect());
	return path;
}

QRectF WAOval::strokeRect() const
{
	qreal sw = stroke().widthF();

	switch(strokePosition()){
	case StrokePosition::Inner:
		return this->rect().adjusted(sw/2, sw/2, -sw/2, -sw/2);
		break;
	case StrokePosition::Outer:
		return this->rect().adjusted(-sw/2, -sw/2, sw/2, sw/2);
		break;
	case StrokePosition::Center:
	default:
		return this->rect();
		break;
	}
}

QRectF WAOval::adjustedRect() const
{
	qreal sw = stroke().widthF();

	switch(strokePosition()){
	case StrokePosition::Inner:
		return this->rect();
		break;
	case StrokePosition::Outer:
		return this->rect().adjusted(-sw, -sw, sw, sw);
		break;
	case StrokePosition::Center:
	default:
		return this->rect().adjusted(-sw/2, -sw/2, sw/2, sw/2);
		break;
	}
}

/***************************************************
 *
 * Events
 *
 ***************************************************/

void WAOval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
    Q_UNUSED(widget);

//	painter->setClipRect( option->exposedRect );
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setBrush(this->fills());
	painter->drawEllipse(this->rect());
	painter->setBrush(Qt::NoBrush);
	painter->setPen(this->stroke());
	painter->drawEllipse(this->strokeRect());

	painter->setRenderHint(QPainter::Antialiasing, false);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);

}
