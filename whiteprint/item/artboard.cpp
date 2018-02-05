#include "artboard.h"
#include <QDebug>
#include <QFont>
#include "stroke.h"

/*********************
 *
 * Artboard Label
 *
 *********************/

ArtboardLabel::ArtboardLabel(QString name, Artboard *parent) : QGraphicsTextItem(name)
{


	this->setFlags(/*QGraphicsItem::ItemIsSelectable |*/
				   QGraphicsItem::ItemIsFocusable |
				   QGraphicsItem::ItemIgnoresTransformations
				   );

	this->setTextInteractionFlags(Qt::NoTextInteraction);
}

//void ArtboardLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//	QGraphicsTextItem::paint(painter, option, widget);
//}

void ArtboardLabel::focusOutEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setTextInteractionFlags(Qt::NoTextInteraction);
}

void ArtboardLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//	Q_UNUSED(event);

	if (this->textInteractionFlags() == Qt::NoTextInteraction)
			this->setTextInteractionFlags(Qt::TextEditorInteraction);
	setFocus();
	QGraphicsTextItem::mouseDoubleClickEvent(event);
}


/*******************************************************************************************************************************/

/*********************
 *
 * Artboard
 *
 *********************/

Artboard::Artboard(QString name, QGraphicsItem *parent) : Artboard(name, 0,0,375,667, parent){}
Artboard::Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent) : Artboard(name, QRectF(x,y,w,h), parent){}
Artboard::Artboard(QString name, QRectF rect, QGraphicsItem *parent) : ItemBase(/*rect, */parent)
{
	m_offset= 20;
	m_buffer = 4;
	m_rect = rect;
	Stroke stroke("ArtboardStroke", QBrush(QColor(0,0,0, 20)), 0);

	/*
	 * Slow down zoom effect
	 */
	m_shadow = new QGraphicsDropShadowEffect();
	m_shadow->setOffset(0,0);
	m_shadow->setColor(QColor(0,0,0));
	m_shadow->setBlurRadius(m_buffer);

	m_artboard = new QGraphicsRectItem(m_rect);
//	m_artboard->setGraphicsEffect(m_shadow);
	m_artboard->setFlags(
				QGraphicsItem::ItemClipsChildrenToShape |
				QGraphicsItem::ItemContainsChildrenInShape |
				QGraphicsItem::ItemSendsScenePositionChanges |
				QGraphicsItem::ItemSendsGeometryChanges
				);
	m_artboard->setPen(Qt::NoPen);
	m_artboard->setBrush(Qt::NoBrush);
    m_artboard->setParentItem(this);

	m_label = new ArtboardLabel(name, this);
	m_label->setParentItem(this);
	m_label->setPos(this->rect().x(), this->rect().y() - m_offset);

//	this->setFlag(QGraphicsItem::ItemIsSelectable, true);
//	this->setFlag(QGraphicsItem::ItemIsMovable, true);

	this->setFlags(/*QGraphicsItem::ItemIsSelectable |*/
				   //QGraphicsItem::ItemIsPanel |
				   QGraphicsItem::ItemSendsScenePositionChanges |
				   QGraphicsItem::ItemSendsGeometryChanges
				);
    this->setAcceptHoverEvents(true);
    this->setName(name);
	this->addStroke(stroke);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QGraphicsRectItem * Artboard::canvas() const
{
    return m_artboard;
}

void Artboard::setRect(QRectF rect)
{
    m_rect = rect;
    update();
    m_artboard->setRect(rect);
    m_artboard->update();

}

QRectF Artboard::rect() const
{
    return m_rect;
}

QRectF Artboard::boundingRect() const
{
    return QRectF(rect().x() - m_buffer, rect().y() - m_offset - m_buffer, rect().width() + 2 * m_buffer, rect().height() + m_offset + 2 * m_buffer);
}


/***************************************************
 *
 * Events
 *
 ***************************************************/

void Artboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

	painter->setRenderHint(QPainter::Antialiasing, false);

	// draw background
	painter->setPen(Qt::NoPen);
	painter->setBrush(QBrush(Qt::white));
	painter->drawRect(this->rect());

	// zoom level
	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

	// draw grid
	if (lod > 10 ) {

		painter->setClipRect( this->boundingRect());//option->exposedRect );

		const int gridSize = 1;

		qreal left = int(rect().left()) - (int(rect().left()) % gridSize);
		qreal top = int(rect().top()) - (int(rect().top()) % gridSize);

		QVarLengthArray<QLineF, 100> lines;

		for (qreal x = left; x < rect().right(); x += gridSize)
			lines.append(QLineF(x, rect().top(), x, rect().bottom()));
		for (qreal y = top; y < rect().bottom(); y += gridSize)
			lines.append(QLineF(rect().left(), y, rect().right(), y));

		painter->setPen(this->stroke());
		painter->drawLines(lines.data(), lines.size());

	}

	// draw border outside of canvas
	painter->setPen(this->stroke());
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(this->rect().adjusted(-1/lod,-1/lod,1/lod,1/lod));

	// reset painter
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);

}

