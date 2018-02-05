#include "warect.h"

#include <QtWidgets>
#include "itemeffects.h"
#include "shadow.h"
#include <QTransform>

QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

WARect::WARect(QGraphicsItem *parent) : WARect(0,0,300,350, parent){}
WARect::WARect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(x,y,width,height), parent){}
WARect::WARect(qreal width, qreal height, QGraphicsItem *parent) : WARect(QRectF(0,0,width,height), parent){}
WARect::WARect(QRectF rect, QGraphicsItem *parent) : ItemBase(parent){

	m_radiusTL = 0;
	m_radiusTR = 0;
	m_radiusBR = 0;
	m_radiusBL = 0;
	m_boundingRect = rect;
	this->setRect(rect);

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
	setRadius(radius, radius, radius, radius);
}

void WARect::setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft)
{
	m_radiusTL = topleft;
	m_radiusTR = topright;
	m_radiusBR = bottomright;
	m_radiusBL = bottomleft;

	update();
}

void WARect::setRect(QRectF rect)
{
	m_rect = rect.normalized();

	this->setTransformOriginPoint(rect.center());
	this->update();

}

QRectF WARect::rect() const
{
	return m_rect;
}

QRectF WARect::boundingRect() const
{
	return m_boundingRect;
}


QPainterPath WARect::shape() const
{
	return shapeScaled(1);
}

QPainterPath WARect::shapeStroke(Stroke stroke) const
{
	return shapeScaled(1, 0, stroke);
}

QPainterPath WARect::shapeScaled(qreal scaleFactor, qreal offset, Stroke stroke) const
{
	QPainterPath path;
	qreal m_offset = 0;

	qreal sw = stroke.widthF();

	switch(stroke.strokePosition()){
	case StrokePosition::Inner:
		m_offset = sw/2;
		break;
	case StrokePosition::Outer:
		m_offset = -sw/2;
		break;
	case StrokePosition::Center:
	default:
		break;
	}

	QRectF tmpRect = rect().adjusted(-offset, -offset, offset, offset);

	qreal l = (tmpRect.left() + m_offset) * scaleFactor;
	qreal t = (tmpRect.top() + m_offset) * scaleFactor;
	qreal r = (tmpRect.right() -m_offset) * scaleFactor;
	qreal b = (tmpRect.bottom() - m_offset) * scaleFactor;
	qreal w = (tmpRect.width() - offset * 2) / 2 * scaleFactor;
	qreal h = (tmpRect.height() - offset * 2) / 2 * scaleFactor;
	qreal tl = m_radiusTL * scaleFactor;
	qreal tr = m_radiusTR * scaleFactor;
	qreal br = m_radiusBR * scaleFactor;
	qreal bl = m_radiusBL * scaleFactor;

	if (w <= 0 || h <= 0) {
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

	tl = tl*2 - (m_offset - offset * scaleFactor) * 2;
	tr = tr*2 - (m_offset - offset * scaleFactor) * 2;
	br = br*2 - (m_offset - offset * scaleFactor) * 2;
	bl = bl*2 - (m_offset - offset * scaleFactor) * 2;

	path.arcMoveTo(l, t, tl, tl, 180);
	if(tl<=0){
		path.lineTo(l, t);
	}else path.arcTo(l, t, tl, tl, 180, -90); // TL

	if(tr<=0){
		path.lineTo(r, t);
	}else path.arcTo(r-tr, t, tr, tr, 90, -90); // TR

	if(br<=0){
		path.lineTo(r, b);
	}else path.arcTo(r-br, b-br, br, br, 0, -90); // BR

	if(bl<=0){
		path.lineTo(l, b);
	}else path.arcTo(l, b-bl, bl, bl, 270, -90); // BL

	path.closeSubpath();

	return path;
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

	setScaleFactor(option->levelOfDetailFromTransform(painter->transform()));

//	painter->save();
//	painter->setCompositionMode(QPainter::CompositionMode_Destination);
//	painter->fillPath(this->shape(), QBrush(Qt::red));


//	painter->restore();

	// reset bounding box to minimum shape
	m_boundingRect = rect();
	QPainterPath shape = this->shape();
	QPainterPath scaledShape = this->shapeScaled(scaleFactor());

//	QPixmap background(shape.boundingRect().size().toSize());




//	qDebug() << "bgPainter" << bgPainter.viewport();
//	painter->setOpacity(0.5);


	// Draw Shadows
	if(scaleFactor() <= 12){
		foreach(Shadow shadow, shadowList()) {
		m_boundingRect = m_boundingRect.united(drawShadow(shadow, painter, shapeScaled(scaleFactor(), shadow.spread())));
		}
	}

	// Draw Fills
	foreach(Fills fills, fillsList()) {
		drawFills(fills, painter, shape);
	}

	// Draw InnerShadows
	if(scaleFactor() <= 12){
		foreach(Shadow shadow, innerShadowList()) {
			drawInnerShadow(shadow, painter,shape, shapeScaled(scaleFactor(), -shadow.spread()), scaledShape);
		}
	}

	// Draw Strokes
	foreach(Stroke stroke, strokeList()) {
		m_boundingRect = m_boundingRect.united(drawStrokes(stroke, painter,shapeStroke(stroke)));
	}

//	// Draw Blur
//	m_boundingRect = m_boundingRect.united(drawBlur(shape.boundingRect(), painter, 10) );


//		QPen pen(Qt::black);
//		pen.setCosmetic(true);
//		painter->setPen(pen);
//		painter->drawRect(boundingRect());



}
