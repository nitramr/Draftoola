#include "itemeffects.h"
#include <QPainter>
#include <QPaintEngine>
#include <QPixmap>
#include <QDebug>

QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

const qreal radiusScale = qreal(2.5);

ItemEffects::ItemEffects(QObject *parent) : QGraphicsEffect(parent){

	m_shadowRadius = 4;
	m_blurRadius = 0;
	m_shadowList = QList<Shadow>();

}

QRectF ItemEffects::boundingRectFor(const QRectF &rect) const
{
	QRectF newBoundingBox = rect;

	// DropShadow
	const qreal delta = radiusScale * m_shadowRadius + 1;
	QRectF shadowRect = newBoundingBox.adjusted(-delta, -delta, delta, delta);

	rect.united(shadowRect);

	return shadowRect;//rect;
}

void ItemEffects::setShadowList(QList<Shadow> shadowList)
{
	m_shadowList = shadowList;
}

void ItemEffects::setFillsList(QList<Fills> fillsList)
{
	m_fillsList = fillsList;
}

void ItemEffects::setShape(QPainterPath shape)
{
	m_shape = shape;
	update();
}

void ItemEffects::setBlurRadius(qreal radius)
{
	m_blurRadius = radius;
}

void ItemEffects::draw(QPainter *painter)
{

	QPoint offset;

	if (sourceIsPixmap()) {
		// No point in drawing in device coordinates (pixmap will be scaled anyways).
		const QPixmap pixmap = sourcePixmap(Qt::LogicalCoordinates, &offset);

		qDebug() << "SourceIsPixmap";

		painter->drawPixmap(offset, pixmap);
	} else {

		// Draw pixmap in device coordinates to avoid pixmap scaling;

		PixmapPadMode mode = PadToEffectiveBoundingRect;
		if (painter->paintEngine()->type() == QPaintEngine::OpenGL2)
			mode = NoPad;

		const QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset, mode);

		qreal lod = painter->worldTransform().m11();

		if(lod <= 12){
			// Draw DropShadow
			foreach(Shadow shadow, m_shadowList){
				drawShadow(shadow, painter,offset,pixmap);
			}
		}

//		// Draw Fills
//		foreach(Fills fills, m_fillsList){
//			drawFills(fills, painter);
//		}

		// Draw Item
		if(m_blurRadius == 0){

			painter->save();
			painter->setWorldTransform(QTransform());
			painter->drawPixmap(offset, pixmap);
			painter->restore();
		}else drawBlur(painter, offset, pixmap);

		Shadow innerShadow(QColor(Qt::blue), 10, QPoint(5,5));
		//drawShadow(innerShadow, painter,offset,pixmap, true);

	}

}


void ItemEffects::drawShadow(Shadow shadow, QPainter *p, const QPointF &pos, const QPixmap &px, bool isInnerShadow) const
{
	if (px.isNull())
		return;

	qreal scaleFactor = p->worldTransform().m22();

	QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(0);
	QPainter tmpPainter(&tmp);
	tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
	tmpPainter.drawPixmap(QPointF(shadow.offset().x()*scaleFactor, shadow.offset().y()*scaleFactor), px);
	tmpPainter.end();

	// blur the alpha channel
	QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
	blurred.fill(0);
	QPainter blurPainter(&blurred);
	qt_blurImage(&blurPainter, tmp, shadow.radius()*scaleFactor, false, true);
	blurPainter.end();

	// tint the image...
	QPainter blackenPainter(&blurred);
	if(isInnerShadow){
		blackenPainter.setCompositionMode(QPainter::CompositionMode_SourceOut);
	}else blackenPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	blackenPainter.fillRect(blurred.rect(), QBrush(shadow.color()));
	blackenPainter.end();

	p->save();

	if(isInnerShadow){
		p->setRenderHint(QPainter::Antialiasing, true);
		p->setClipPath(m_shape);
	}else p->setRenderHint(QPainter::Antialiasing, false);

	p->setWorldTransform(QTransform());
	p->drawImage(pos, blurred);
	p->restore();
}


void ItemEffects::drawBlur(QPainter *p, const QPointF &pos, const QPixmap &px) const
{
	if (px.isNull())
		return;

	qreal scaleFactor = p->worldTransform().m11();

	QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(0);
	QPainter tmpPainter(&tmp);
	tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
	tmpPainter.drawPixmap(QPointF(0,0), px);
	tmpPainter.end();

	// blur the alpha channel
	QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
	blurred.fill(0);
	QPainter blurPainter(&blurred);
	qt_blurImage(&blurPainter, tmp, m_blurRadius*scaleFactor, false, false);
	blurPainter.end();

	p->save();
	p->setRenderHint(QPainter::Antialiasing, false);
	p->setWorldTransform(QTransform());
	p->drawImage(pos, blurred);
	p->restore();
}

void ItemEffects::drawFills(Fills fills, QPainter *p) const
{
	p->save();
	p->setBrush(fills);
	p->drawPath(m_shape);
	p->restore();
}


