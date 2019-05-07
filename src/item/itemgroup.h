#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QGraphicsItemGroup>
#include "itembase.h"

class ItemGroup : /*public QGraphicsItemGroup, */public ItemBase
{

public:
    explicit ItemGroup(QGraphicsItem *parent = nullptr);

	// Properties
	void setRect(QRectF rect);

signals:

public slots:
};

#endif // WAGROUP_H
