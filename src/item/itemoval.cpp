#include "itemoval.h"

ItemOval::ItemOval(QGraphicsItem *parent) : ItemOval(0,0,300,350, parent){}
ItemOval::ItemOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(x,y,width,height), parent){}
ItemOval::ItemOval(qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(0,0,width,height), parent){}
ItemOval::ItemOval(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent){

    this->setRect(rect);
    this->setItemType(ItemType::Oval);

}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemOval::setRect(QRectF rect)
{
    QPainterPath path;
    path.addEllipse(rect);
    ItemBase::setShape(path); // setRect() will set by setShape()
}

