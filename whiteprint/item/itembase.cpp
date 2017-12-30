#include "itembase.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>

#include <QGraphicsDropShadowEffect>

ItemBase::ItemBase(QGraphicsItem *parent): ItemBase(0,0,30,30, parent){}
ItemBase::ItemBase(qreal x, qreal y, qreal w, qreal height, QGraphicsItem *parent) : ItemBase(QRectF(x,y,w,height), parent){}
ItemBase::ItemBase(QRectF rect, QGraphicsItem *parent) : QGraphicsItem(parent),
  m_fills(Fills("initFills", QColor(255,255,255,255))),
  m_stroke(Stroke("initStroke", QBrush(QColor(0,0,0,255)),1.0)),
  m_rect(rect)
{
    m_itemType = ItemType::Rect;
    m_name = "";

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

void ItemBase::setRect(QRectF rect)
{
    m_rect = rect;
    update();
}

QRectF ItemBase::rect() const
{
	return m_rect;
}

QRectF ItemBase::rectAdjusted() const
{
	QRectF rectAdj(rect().x() + 0.5,
				  rect().y() + 0.5,
				  rect().width() - 1,
				  rect().height() - 1);
	return rectAdj;
}

QRectF ItemBase::boundingRect() const
{
	return m_rect;
}

void ItemBase::setStroke(Stroke stroke)
{
	m_stroke = stroke;
}

Stroke ItemBase::stroke() const
{
	return m_stroke;
}

void ItemBase::setFills(Fills fills)
{
	m_fills = fills;
}

Fills ItemBase::fills() const
{
	return m_fills;
}

qreal ItemBase::width() const
{
    return m_rect.width();
}

qreal ItemBase::height() const
{
    return m_rect.height();
}

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

/***************************************************
 *
 * Events
 *
 ***************************************************/

void ItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

	painter->setPen(stroke());
	painter->fillRect(rect(), fills());
	painter->drawRect(rectAdjusted());

}



