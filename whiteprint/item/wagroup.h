#ifndef WAGROUP_H
#define WAGROUP_H

#include <QGraphicsItemGroup>
#include "itembase.h"

class WAGroup : /*public QGraphicsItemGroup, */public ItemBase
{

public:
	explicit WAGroup(QGraphicsItem *parent = 0);

	// Properties
	QRectF rect() const;
	void setRect(QRectF rect);

signals:

public slots:
};

#endif // WAGROUP_H
