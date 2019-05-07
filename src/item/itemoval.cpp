#include "itemoval.h"

ItemOval::ItemOval(QGraphicsItem *parent) : ItemOval(0,0,300,350, parent){}
ItemOval::ItemOval(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(x,y,width,height), parent){}
ItemOval::ItemOval(qreal width, qreal height, QGraphicsItem *parent) : ItemOval(QRectF(0,0,width,height), parent){}
ItemOval::ItemOval(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent){

    this->setRect(rect);

    this->setItemType(ItemType::Oval);
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

void ItemOval::setRect(QRectF rect)
{
    QPainterPath path;
    path.addEllipse(rect);
    ItemBase::setShape(path); // setRect() will set by setShape()
}


/***************************************************
 *
 * Events
 *
 ***************************************************/

//void ItemOval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
////    ItemBase::paint(painter, option, widget);

//    painter->save();

//    // BoundingBox
//    QPen pen = QPen(QColor(0,0,0));
//    pen.setCosmetic(true);
//    pen.setStyle(Qt::PenStyle::DotLine);
//    painter->setPen(pen);
//    painter->drawRect(this->boundingRect());

//    painter->restore();

//    qDebug() << "ItemOval::Paint" << boundingRect() << rect();
//}
