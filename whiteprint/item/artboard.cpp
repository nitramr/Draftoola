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
Artboard::Artboard(QString name, QRectF rect, QGraphicsItem *parent) : ItemBase(parent),
    m_offset(20),
    m_buffer(4),
    m_rect(rect)
{

	Stroke stroke("ArtboardNoneStroke", Qt::transparent, 0);

	/*
	 * Slow down zoom effect
	 */
//	m_shadow = new QGraphicsDropShadowEffect();
//	m_shadow->setOffset(0,0);
//	m_shadow->setColor(QColor(0,0,0));
//	m_shadow->setBlurRadius(m_buffer);

    m_artboard = new ItemBase(m_rect);
//	m_artboard->setGraphicsEffect(m_shadow);
    m_artboard->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_artboard->setFlag(QGraphicsItem::ItemIsFocusable, false);
	m_artboard->setStroke(stroke);
    m_artboard->setParentItem(this);

	m_label = new ArtboardLabel(name, this);
	m_label->setParentItem(this);
	m_label->setPos(this->rect().x(), this->rect().y() - m_offset);


    this->setFlag(QGraphicsItem::ItemIsPanel, true);
	this->setFlag(QGraphicsItem::ItemIsSelectable, false);
//	this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setAcceptHoverEvents(true);
    this->setName(name);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QGraphicsItem * Artboard::canvas() const
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

	painter->setPen(QPen(QColor(180,180,180)));
	painter->drawRect(this->adjustedRect());




//	painter->setClipRect( this->boundingRect());//option->exposedRect );

//	const int gridSize = 25;

//	qreal left = int(rect().left()) - (int(rect().left()) % gridSize);
//	qreal top = int(rect().top()) - (int(rect().top()) % gridSize);

//	QVarLengthArray<QLineF, 100> lines;

//	for (qreal x = left; x < rect().right(); x += gridSize)
//		lines.append(QLineF(x + 0.5, rect().top(), x + 0.5, rect().bottom()));
//	for (qreal y = top; y < rect().bottom(); y += gridSize)
//		lines.append(QLineF(rect().left(), y + 0.5, rect().right(), y + 0.5));

//	//qDebug() << lines.size();

//	painter->setPen(QPen(QColor(200,200,200)));
//	painter->drawLines(lines.data(), lines.size());


}

