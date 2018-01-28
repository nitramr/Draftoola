#include "warect.h"

#include <QtWidgets>
#include "itemeffects.h"
#include "shadow.h"

WARect::WARect(QGraphicsItem *parent) : WARect(0,0,300,350, parent){}
WARect::WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(x,y,width,height), parent){}
WARect::WARect(qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(0,0,width,height), parent){}
WARect::WARect(QRectF rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent){

	m_radiusTL = 0;
	m_radiusTR = 0;
	m_radiusBR = 0;
	m_radiusBL = 0;

	this->setItemType(ItemType::Rect);
	this->setFlags(QGraphicsItem::ItemIsSelectable |
				   QGraphicsItem::ItemIsFocusable |
				   QGraphicsItem::ItemClipsChildrenToShape |
				   QGraphicsItem::ItemContainsChildrenInShape |
				   QGraphicsItem::ItemSendsScenePositionChanges |
				   QGraphicsItem::ItemSendsGeometryChanges
				   );
	this->setAcceptHoverEvents(true);
	this->setGraphicsEffect(itemEffects());



}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void WARect::setRadius(qreal radius)
{
	setRadius(radius, radius, radius, radius);
}

void WARect::setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft)
{
	m_radiusTL = topleft;
	m_radiusTR = topright;
	m_radiusBR = bottomright;
	m_radiusBL = bottomleft;
}


QPainterPath WARect::shape() const
{
	return shapeStroke(Stroke("tmp", QColor(Qt::transparent),StrokePosition::Center));
}

QPainterPath WARect::shapeStroke(Stroke stroke) const
{
	QPainterPath path;
	qreal offset = 0;

	qreal sw = stroke.widthF();

	switch(stroke.strokePosition()){
	case StrokePosition::Inner:
		offset = sw/2;
		break;
	case StrokePosition::Outer:
		offset = -sw/2;
		break;
	case StrokePosition::Center:
	default:
		break;
	}

	qreal l = rect().left() + offset;
	qreal t = rect().top() + offset;
	qreal r = rect().right() -offset;
	qreal b = rect().bottom() - offset;
	qreal w = rect().width() / 2;
	qreal h = rect().height() / 2;
	qreal tl = m_radiusTL;
	qreal tr = m_radiusTR;
	qreal br = m_radiusBR;
	qreal bl = m_radiusBL;

	if (w == 0 || h == 0) {
		bl = 0;
		br = 0;
		tr = 0;
		tl = 0;
	} else {
		qreal blW, blH;
		blW = qMin(bl, w);
		blH = qMin(bl, h);
		bl = qMin(blH, blW);

		qreal brW, brH;
		brW = qMin(br, w);
		brH = qMin(br, h);
		br = qMin(brH, brW);

		qreal trW, trH;
		trW = qMin(tr, w);
		trH = qMin(tr, h);
		tr = qMin(trH, trW);

		qreal tlW, tlH;
		tlW = qMin(tl, w);
		tlH = qMin(tl, h);
		tl = qMin(tlH, tlW);
	}

	tl = tl*2 - offset*2;
	tr = tr*2 - offset*2;
	br = br*2 - offset*2;
	bl = bl*2 - offset*2;

	path.arcMoveTo(l, t, tl, tl, 180);
	if(tl==0){
		path.lineTo(l, t);
	}else path.arcTo(l, t, tl, tl, 180, -90); // TL

	if(tr==0){
		path.lineTo(r, t);
	}else path.arcTo(r-tr, t, tr, tr, 90, -90); // TR

	if(br==0){
		path.lineTo(r, b);
	}else path.arcTo(r-br, b-br, br, br, 0, -90); // BR

	if(bl==0){
		path.lineTo(l, b);
	}else path.arcTo(l, b-bl, bl, bl, 270, -90); // BL

	path.closeSubpath();

	return path;
}

QRectF WARect::boundingRect() const
{
	QRectF boundingBox = rect();

	if(this->graphicsEffect() != 0){
		ItemEffects *effect = dynamic_cast<ItemEffects*>(this->graphicsEffect());
		if(effect)
			boundingBox = effect->boundingRectFor(rect());
	}

	return boundingBox;



	//return QGraphicsRectItem::boundingRect();
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


	setShape(shape());
	//	painter->setClipRect( option->exposedRect );

	painter->save();
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::Antialiasing, true);

//	painter->setBrush(QBrush(Qt::black));
//	painter->drawPath(shape());
//	painter->setBrush(Qt::NoBrush);

	// Draw Fills
	foreach(Fills fills, fillsList()) {
		painter->setBrush(fills);
		painter->drawPath(shape());
	}

	painter->setBrush(Qt::NoBrush);

	// Draw Strokes
	foreach(Stroke stroke, strokeList()) {
		painter->setPen(stroke);
		painter->drawPath(shapeStroke(stroke));
	}

	//	QPen pen(Qt::black);
	//	pen.setCosmetic(true);
	//	painter->setPen(pen);
	//	painter->drawRect(boundingRect());

	painter->restore();

}
