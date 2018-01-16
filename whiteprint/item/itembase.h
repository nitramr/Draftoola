#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QPen>
#include <QBrush>
#include <QMap>

#include "itemstruct.h"
#include "stroke.h"
#include "fills.h"
#include "gradient.h"

class ItemBase
{
public:

	ItemBase();


    // Properties
    void setName(QString name);
    QString name() const;
    void setItemType(ItemType type);
    ItemType itemType() const;
	void setStroke(Stroke stroke);
	Stroke stroke() const;
	void setStrokePosition(StrokePosition strokePosition);
	StrokePosition strokePosition() const;
	void setFills(Fills fills);
	Fills fills() const;

	// Members
	void addExportFactor(QString key, double value);
	void removeExportFactor(QString key);


private:
	// Properties
    QString m_name;
    ItemType m_itemType;
    QRectF m_boundingRect;
	Stroke m_stroke;
	Fills m_fills;
	StrokePosition m_strokePosition;

	// Members
	QMap<QString, double> m_exportFactorList;

};

#endif // ITEMBASE_H
