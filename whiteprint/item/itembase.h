#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QGraphicsEffect>
#include <QImage>

#include "itemeffects.h"
#include "itemstruct.h"
#include "stroke.h"
#include "fills.h"
#include "gradient.h"
#include "shadow.h"

class ItemBase
{
public:

	ItemBase();


    // Properties
    void setName(QString name);
    QString name() const;
    void setItemType(ItemType type);
    ItemType itemType() const;

	void addStroke(Stroke stroke);
	Stroke stroke(int id = 0) const;
	QList<Stroke> strokeList() const;

	void addFills(Fills fills);
	Fills fills(int id = 0) const;
	QList<Fills> fillsList() const;

	void addShadow(Shadow shadow);
	Shadow shadow(int id = 0) const;
	QList<Shadow> shadowList() const;

	void setShape(QPainterPath shape);

	ItemEffects *itemEffects() const;

	// Members
	void addExportFactor(QString key, double value);
	void removeExportFactor(QString key);


private:
	// Properties
    QString m_name;
    ItemType m_itemType;
    QRectF m_boundingRect;
	StrokePosition m_strokePosition;

	// Members
	ItemEffects *			m_effects;
	QMap<QString, double>	m_exportFactorList;
	QList<Fills>			m_fillsList;
	QList<Stroke>			m_strokeList;
	QList<Shadow>			m_shadowList;

};

#endif // ITEMBASE_H
