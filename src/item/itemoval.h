#ifndef ITEMOVAL_H
#define ITEMOVAL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>


#include "itembase.h"

class ItemOval : public ItemBase
{
public:
    ItemOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemOval(qreal width, qreal height, QGraphicsItem * parent = nullptr);
    ItemOval(QRectF rect, QGraphicsItem * parent = nullptr);
    ItemOval(QGraphicsItem * parent = nullptr);

	// Properties
    int type() const override { return Type::Oval; }
    void setRect(QRectF rect) override;

};

#endif // ITEMOVAL_H
