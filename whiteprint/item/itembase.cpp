#include "itembase.h"
#include <QDebug>


ItemBase::ItemBase() :
  m_fills(Fills("initFills", QColor(255,255,255,255))),
  m_stroke(Stroke("initStroke", QBrush(QColor(0,0,0,255)),1.0))
{
    m_itemType = ItemType::Rect;
    m_name = "";
	m_strokePosition = StrokePosition::Inner;
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

void ItemBase::setStroke(Stroke stroke)
{
	m_stroke = stroke;
}

Stroke ItemBase::stroke() const
{
	return m_stroke;
}

void ItemBase::setStrokePosition(StrokePosition strokePosition)
{
	m_strokePosition = strokePosition;
}

StrokePosition ItemBase::strokePosition() const
{
	return m_strokePosition;
}

void ItemBase::setFills(Fills fills)
{
	m_fills = fills;
}

Fills ItemBase::fills() const
{
	return m_fills;
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
