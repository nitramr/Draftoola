#include "warect.h"

#include <QtWidgets>

WARect::WARect(QGraphicsItem *parent) : WARect(0,0,300,350, parent){}
WARect::WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(x,y,width,height), parent){}
WARect::WARect(qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(0,0,width,height), parent){}
WARect::WARect(QRectF rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent), m_radius(0){
    this->setItemType(ItemType::Rect);

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

void WARect::setRadius(qreal radius)
{
	m_radius = radius;
}

qreal WARect::radius() const
{
	return m_radius;
}

QPainterPath WARect::shape() const
{
	QPainterPath path;
	path.addRoundedRect(adjustedRect(), radius(), radius());
	return path;
}

QRectF WARect::strokeRect() const
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

QRectF WARect::adjustedRect() const
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

QPointF WARect::anchorTopLeft() const
{
	return this->scenePos();
}

QPointF WARect::anchorTop() const
{
	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y());
}

QPointF WARect::anchorTopRight() const
{
	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y());
}

QPointF WARect::anchorRight() const
{
	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height() / 2);
}

QPointF WARect::anchorBottomRight() const
{
	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height());
}

QPointF WARect::anchorBottom() const
{
	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height());
}

QPointF WARect::anchorBottomLeft() const
{
	return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height());
}

QPointF WARect::anchorLeft() const
{
	return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height() / 2);
}

QPointF WARect::anchorCenter() const
{
	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height() / 2);
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
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setBrush(this->fills());
	painter->drawRoundedRect(this->rect(), m_radius, m_radius);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(this->stroke());
	painter->drawRoundedRect(this->strokeRect(), m_radius, m_radius);

	painter->setRenderHint(QPainter::Antialiasing, false);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);


}
