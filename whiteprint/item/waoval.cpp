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
	path.addEllipse(rect());
	return path;
}

QPainterPath WAOval::shapeStroke(Stroke stroke) const
{
	QPainterPath path;
	qreal sw = stroke.widthF();
	QRectF rect = this->rect();

	switch(stroke.strokePosition()){
	case StrokePosition::Inner:
		rect.adjusted(sw/2, sw/2, -sw/2, -sw/2);
		break;
	case StrokePosition::Outer:
		rect.adjusted(-sw/2, -sw/2, sw/2, sw/2);
		break;
	case StrokePosition::Center:
	default:
		break;
	}

	path.addEllipse(rect);
	return path;
}

//QRectF WAOval::adjustedRect(StrokePosition strokePosition) const
//{
//	qreal sw = stroke().widthF();

//	switch(strokePosition()){
//	case StrokePosition::Inner:
//		return this->rect();
//		break;
//	case StrokePosition::Outer:
//		return this->rect().adjusted(-sw, -sw, sw, sw);
//		break;
//	case StrokePosition::Center:
//	default:
//		return this->rect().adjusted(-sw/2, -sw/2, sw/2, sw/2);
//		break;
//	}
//}

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
	painter->save();
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::Antialiasing, true);

	// Draw Fills
	foreach(Fills fills,this->fillsList()) {
		painter->setBrush(fills);
		painter->drawPath(shape());
	}

	painter->setBrush(Qt::NoBrush);

	// Draw Strokes
	foreach(Stroke stroke, strokeList()) {
		painter->setPen(stroke);
		painter->drawPath(shapeStroke(stroke));
	}

	painter->restore();

}
