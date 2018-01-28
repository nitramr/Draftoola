#include "itembase.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QLabel>

QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

const qreal radiusScale = qreal(2.5);

ItemBase::ItemBase()
{

	Fills fills("initFills", QColor(255,255,255,255));
	Stroke stroke("initStroke", QBrush(QColor(0,0,0,255)),1.0);

    m_itemType = ItemType::Rect;
    m_name = "";
	m_strokePosition = StrokePosition::Inner;
	m_fillsList = QList<Fills>();
//	m_fillsList.append(fills);
	m_strokeList = QList<Stroke>();
//	m_strokeList.append(stroke);
	m_shadowList = QList<Shadow>();

	m_effects = new ItemEffects();
	m_effects->setShadowList(m_shadowList);
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
	m_effects->setFillsList(m_fillsList);
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
	m_effects->setShadowList(m_shadowList);
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

void ItemBase::setShape(QPainterPath shape)
{
	m_effects->setShape(shape);
}

ItemEffects *ItemBase::itemEffects() const
{
	return m_effects;
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
