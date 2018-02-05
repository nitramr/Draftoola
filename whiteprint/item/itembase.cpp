#include "itembase.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QLabel>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
// https://code.woboq.org/qt5/qtbase/src/widgets/effects/qpixmapfilter.cpp.html
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

ItemBase::ItemBase(QGraphicsItem *parent) : QGraphicsObject(parent)
{
	m_itemType = ItemType::Rect;
	m_name = "";
	m_strokePosition = StrokePosition::Inner;
	m_fillsList = QList<Fills>();
	m_strokeList = QList<Stroke>();
	m_shadowList = QList<Shadow>();
	m_innerShadowList = QList<Shadow>();

	m_scaleFactor = 1;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemBase::setName(QString name)
{
	m_name = name;
}

QString ItemBase::name() const
{
	return m_name;
}

void ItemBase::setItemType(ItemType type)
{
	m_itemType = type;
}

ItemType ItemBase::itemType() const
{
	return m_itemType;
}

void ItemBase::addStroke(Stroke stroke)
{
	m_strokeList.append(stroke);
}

Stroke ItemBase::stroke(int id) const
{
	id = qMin(m_strokeList.size()-1, qMax(0, id));
	return m_strokeList.at(id);
}

QList<Stroke> ItemBase::strokeList() const
{
	return m_strokeList;
}

void ItemBase::addFills(Fills fills)
{
	m_fillsList.append(fills);
}

Fills ItemBase::fills(int id) const
{
	id = qMin(m_fillsList.size()-1, qMax(0, id));
	return m_fillsList.at(id);
}

QList<Fills> ItemBase::fillsList() const
{
	return m_fillsList;
}

void ItemBase::addShadow(Shadow shadow)
{
	m_shadowList.append(shadow);
}

Shadow ItemBase::shadow(int id) const
{
	id = qMin(m_shadowList.size()-1, qMax(0, id));
	return m_shadowList.at(id);
}

QList<Shadow> ItemBase::shadowList() const
{
	return m_shadowList;
}

void ItemBase::addInnerShadow(Shadow shadow)
{
	m_innerShadowList.append(shadow);
}

Shadow ItemBase::innerShadow(int id) const
{
	id = qMin(m_innerShadowList.size()-1, qMax(0, id));
	return m_innerShadowList.at(id);
}

QList<Shadow> ItemBase::innerShadowList() const
{
	return m_innerShadowList;
}

void ItemBase::setScaleFactor(qreal scaleFactor)
{
	m_scaleFactor = scaleFactor;
}

qreal ItemBase::scaleFactor() const
{
	return m_scaleFactor;
}

//void ItemBase::setRect(QRectF rect)
//{
//	m_rect = rect.normalized();

//	this->setTransformOriginPoint(rect.center());
//}

//QRectF ItemBase::rect() const
//{
//	return m_rect;
//}

//QRectF ItemBase::boundingRect() const
//{
//	return m_boundingRect;
//}

//void ItemBase::setShape(QPainterPath shape)
//{
//	m_shape = shape;
//}

//QPainterPath ItemBase::shape() const
//{
//	return m_shape;
//}


//QPointF ItemBase::anchorTopLeft() const
//{
//	return this->scenePos();
//}

//QPointF ItemBase::anchorTop() const
//{
//	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y());
//}

//QPointF ItemBase::anchorTopRight() const
//{
//	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y());
//}

//QPointF ItemBase::anchorRight() const
//{
//	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height() / 2);
//}

//QPointF ItemBase::anchorBottomRight() const
//{
//	return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height());
//}

//QPointF ItemBase::anchorBottom() const
//{
//	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height());
//}

//QPointF ItemBase::anchorBottomLeft() const
//{
//	return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height());
//}

//QPointF ItemBase::anchorLeft() const
//{
//	return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height() / 2);
//}

//QPointF ItemBase::anchorCenter() const
//{
//	return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height() / 2);
//}

/***************************************************
 *
 * Members
 *
 ***************************************************/


void ItemBase::addExportFactor(QString key, double value){
	m_exportFactorList.insert(key, value);
}

void ItemBase::removeExportFactor(QString key){
	m_exportFactorList.remove(key);
}

QRectF ItemBase::drawShadow(Shadow shadow, QPainter *painter, QPainterPath shapeScaled)
{
	painter->save();
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setRenderHint(QPainter::SmoothPixmapTransform, true);


	// plain values
	qreal m_offsetX = shadow.offset().x();
	qreal m_offsetY = shadow.offset().y();
	qreal m_spread = shadow.spread();
	qreal m_radiusShadow = shadow.radius();
	qreal m_width = shapeScaled.boundingRect().width();
	qreal m_height = shapeScaled.boundingRect().height();
	QColor m_color = shadow.color();


	// calculated values
	qreal buffer = m_radiusShadow + m_spread;
	qreal radiusScale = m_radiusShadow * scaleFactor();
	qreal spreadScale = m_spread * scaleFactor();

	QImage shadowMap;

	//	if(shadowMapRedraw){

	// Draw Shadow Pixmap
	QPixmap px(m_width + radiusScale * 2, m_height + radiusScale * 2);
	QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(0);
	QPainter pxPainter(&tmp);
	pxPainter.setRenderHint(QPainter::Antialiasing, true);
	pxPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	pxPainter.translate(QPointF(radiusScale + spreadScale,radiusScale + spreadScale));
	pxPainter.setBrush(QBrush(m_color));
	pxPainter.setPen(Qt::NoPen);
	pxPainter.drawPath(shapeScaled);
	pxPainter.end();

	// blur the alpha channel
	QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
	blurred.fill(0);
	QPainter blurPainter(&blurred);
	qt_blurImage(&blurPainter, tmp, radiusScale, false, true);
	blurPainter.end();

	//	QPainter tintPainter(&blurred);
	//	tintPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//	tintPainter.fillRect(blurred.rect(), QBrush(m_color));
	//	tintPainter.end();

	shadowMap = blurred;
	//	m_shadowMap = shadowMap;
	//	shadowMapRedraw = false;

	//	}else{
	//		if(!m_shadowMap.isNull()){
	//			shadowMap = m_shadowMap;
	//		}
	//	}

	// bounding rect Shadow
	QRectF target(0 -buffer + m_offsetX,
				  0 -buffer + m_offsetY,
				  m_width / scaleFactor() + m_radiusShadow * 2,
				  m_height / scaleFactor() + m_radiusShadow * 2);

	// draw shadow
	painter->drawImage(target, shadowMap, QRectF(shadowMap.rect()));
	painter->restore();

	return target;

}


//QRectF ItemBase::drawInnerShadow(Shadow shadow, QPainter *painter, QPainterPath clippingShape, QPainterPath shapeScaled, QPainterPath clippingShapeScaled)
//{
//	painter->save();
//	painter->setBrush(Qt::NoBrush);
//	painter->setPen(Qt::NoPen);
//	painter->setRenderHint(QPainter::Antialiasing, true);
//	painter->setRenderHint(QPainter::SmoothPixmapTransform, true);


//	// plain values
//	qreal m_radiusShadow = shadow.radius();
//	QColor m_color = shadow.color();
//	qreal m_widthC = clippingShapeScaled.boundingRect().width() + m_radiusShadow*2 * scaleFactor();
//	qreal m_heightC = clippingShapeScaled.boundingRect().height() + m_radiusShadow*2 * scaleFactor();


//	// calculated values
//	qreal m_offsetX = (m_radiusShadow + shadow.offset().x()) * scaleFactor();
//	qreal m_offsetY = (m_radiusShadow + shadow.offset().y()) * scaleFactor();

////	QImage shadowMap;


////	// Draw Shadow Pixmap
////	QPixmap px(QSize(m_widthC, m_heightC));
////	QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
////	tmp.fill(0);
////	QPainter pxPainter(&tmp);
////	pxPainter.setRenderHint(QPainter::Antialiasing, true);
//////	pxPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
////	pxPainter.translate(QPointF(m_offsetX,m_offsetY));
////	pxPainter.setBrush(QBrush(Qt::black));
////	pxPainter.setPen(Qt::NoPen);
////	pxPainter.drawPath(shapeScaled);
////	pxPainter.end();

////	// blur the alpha channel
////	QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
////	blurred.fill(0);
////	QPainter blurPainter(&blurred);
////	qt_blurImage(&blurPainter, tmp, m_radiusShadow * scaleFactor(), false, true);
////	blurPainter.end();

////	QPainter tintPainter(&blurred);
////	tintPainter.setCompositionMode(QPainter::CompositionMode_SourceOut);
////	tintPainter.fillRect(blurred.rect(), QBrush(m_color));
////	tintPainter.end();

////	shadowMap = blurred;

////	// bounding rect Shadow
////	QRectF target(0-m_radiusShadow,
////				  0-m_radiusShadow,
////				  m_widthC / scaleFactor(),
////				  m_heightC / scaleFactor());

//	// draw shadow
////	painter->setClipPath(clippingShape);

//	if(!m_mask.isNull()){

//		qreal radiusScale = m_radiusShadow * scaleFactor();
//		QRectF rectShape = m_mask.rect().adjusted(-radiusScale, -radiusScale, radiusScale, radiusScale);


//		// Draw Shape
//		QPixmap pxMask(rectShape.size().toSize());
//		pxMask.fill(Qt::transparent);
//		QPainter pFill(&pxMask);
//		pFill.drawPixmap(QPointF(m_offsetX, m_offsetY), m_mask);
//		pFill.end();

//		// Apply blur effect
//		QImage imgBlur = pxMask.toImage();

//		QPixmap pxShadow(rectShape.size().toSize());
//		pxShadow.fill(Qt::transparent);
//		QPainter pBlur(&pxShadow);
//		pBlur.setRenderHint(QPainter::Antialiasing, true);
//		pBlur.setRenderHint(QPainter::SmoothPixmapTransform, true);
//		// Clipping Shape
//		pBlur.translate(radiusScale, radiusScale);
//		pBlur.setClipPath(clippingShapeScaled);
//		pBlur.translate(-radiusScale, -radiusScale);
//		qt_blurImage(&pBlur, imgBlur, radiusScale, false, true);

//		// Invert shape
//		pBlur.setCompositionMode(QPainter::CompositionMode_SourceOut);
//		pBlur.fillRect(rectShape, QBrush(m_color));


//		pBlur.end();


//		QRectF target(0-m_radiusShadow,
//		0-m_radiusShadow,
//		rectShape.width() / scaleFactor(),
//		rectShape.height() / scaleFactor());

//		painter->drawPixmap(target, pxShadow, pxShadow.rect());

//	}

//	painter->restore();

//	return m_mask.rect();

//}

QRectF ItemBase::drawInnerShadow(Shadow shadow, QPainter *painter, QPainterPath clippingShape, QPainterPath shapeScaled, QPainterPath clippingShapeScaled)
{
	painter->save();
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setRenderHint(QPainter::SmoothPixmapTransform, true);


	// plain values
	qreal m_radiusShadow = shadow.radius();
	QColor m_color = shadow.color();
	qreal m_widthC = clippingShapeScaled.boundingRect().width() + m_radiusShadow*2 * scaleFactor();
	qreal m_heightC = clippingShapeScaled.boundingRect().height() + m_radiusShadow*2 * scaleFactor();


	// calculated values
	qreal m_offsetX = (m_radiusShadow + shadow.offset().x()) * scaleFactor();
	qreal m_offsetY = (m_radiusShadow + shadow.offset().y()) * scaleFactor();

	QImage shadowMap;


	// Draw Shadow Pixmap
	QPixmap px(QSize(m_widthC, m_heightC));
	QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(0);
	QPainter pxPainter(&tmp);
	pxPainter.setRenderHint(QPainter::Antialiasing, true);
	//	pxPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	pxPainter.translate(QPointF(m_offsetX,m_offsetY));
	pxPainter.setBrush(QBrush(Qt::black));
	pxPainter.setPen(Qt::NoPen);
	pxPainter.drawPath(shapeScaled);
	pxPainter.end();

	// blur the alpha channel
	QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
	blurred.fill(0);
	QPainter blurPainter(&blurred);
	qt_blurImage(&blurPainter, tmp, m_radiusShadow * scaleFactor(), false, true);
	blurPainter.end();

	QPainter tintPainter(&blurred);
	tintPainter.setCompositionMode(QPainter::CompositionMode_SourceOut);
	tintPainter.fillRect(blurred.rect(), QBrush(m_color));
	tintPainter.end();

	shadowMap = blurred;

	// bounding rect Shadow
	QRectF target(0-m_radiusShadow,
				  0-m_radiusShadow,
				  m_widthC / scaleFactor(),
				  m_heightC / scaleFactor());

	// draw shadow
	painter->setClipPath(painter->clipPath().intersected(clippingShape));
	painter->drawImage(target, shadowMap, QRectF(shadowMap.rect()));

	painter->restore();

	return target;

}

QRectF ItemBase::drawFills(Fills fills, QPainter *painter, QPainterPath shape)
{

	painter->save();

	QRectF shapeRect = shape.boundingRect();

//	QTransform transform = painter->worldTransform();
//	transform.scale(0,0);
//	QBrush brushFills(fills.pixmap());
//	brushFills.setTransform(transform);



	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);

	painter->setCompositionMode(fills.blendMode());
//	painter->setBrushOrigin(20,20);

	switch(fills.fillType()){
	case FillType::Color:{
		painter->setBrush(QBrush(fills.color()));
		painter->drawPath(shape);
		break;
	}
	case FillType::Gradient:{

		QGradient gradient(fills.gradient());

		painter->setBrush(QBrush(gradient));
		painter->drawPath(shape);
		break;
	}
	case FillType::Image:{
		QPixmap texture = fills.pixmap();
		if(!texture.isNull())
		{

			painter->setRenderHint(QPainter::Antialiasing, true);
			painter->setClipPath(painter->clipPath().intersected(shape));


			QRect imgRect;
			qreal xratio = texture.width() / shapeRect.width();
			qreal yratio = texture.height() / shapeRect.height();

			// Respect the aspect ratio mode.
			switch (fills.fillMode()) {
			case FillMode::Fill:
				xratio = yratio = qMin(xratio, yratio);
				break;
			case FillMode::Fit:
				xratio = yratio = qMax(xratio, yratio);
				break;
			case FillMode::Stretch:
				break;
			case FillMode::Tile:

				painter->drawTiledPixmap(shapeRect.toRect(), texture);

				painter->restore();
				return shapeRect;
				break;
			}

			qreal scaledWidth = shapeRect.width() * xratio;
			qreal scaledHeight = shapeRect.height() * yratio;
			qreal xOffset = 0;//(qMax(scaledWidth, shapeRect.width()) - qMin(scaledWidth, shapeRect.width())) /2;
			qreal yOffset = 0;//(qMin(scaledHeight, shapeRect.height()) - qMax(scaledHeight, shapeRect.height())) /2;

			imgRect = QRect(xOffset,yOffset,scaledWidth, scaledHeight);

			//		painter->fillRect(rectShape, Qt::white);
			painter->drawPixmap(shapeRect, texture, imgRect);

		}

		break;
	}
	case FillType::Pattern:
		break;

	}

//	painter->drawPath(shape);

	painter->restore();

	return shapeRect;
}

QRectF ItemBase::drawStrokes(Stroke stroke, QPainter *painter, QPainterPath shape)
{
	painter->save();

	QRectF boundingBox = shape.boundingRect();
	qreal width = stroke.widthF();
	qreal offset = width/2;


//	QPainterPathStroker stroker;
//	stroker.setCapStyle( stroke.capStyle() );
//	stroker.setJoinStyle( stroke.joinStyle()  );
//	stroker.setDashPattern( stroke.dashPattern() );
//	stroker.setWidth( width );
//	QPainterPath outline = stroker.createStroke( shape );

	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);
//	painter->setBrush(stroke.color());
	painter->setPen(stroke);
	painter->drawPath( shape );

	painter->restore();

	return boundingBox.adjusted(-offset,-offset,offset,offset);
}

QRectF ItemBase::drawBlur(QRectF shapeRect, QPainter* painter, qreal radius)
{
	painter->save();

	// Add Blur Logic

	painter->restore();

	return shapeRect;
}
