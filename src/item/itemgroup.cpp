#include <QDebug>
#include "itemgroup.h"
#include "itemoval.h"
#include "itemrect.h"
#include "itemtext.h"

ItemGroup::ItemGroup(QGraphicsItem *parent) : AbstractItemBase(QRectF(), parent){
//    m_group = new QGraphicsItemGroup();

    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    this->setFlag(QGraphicsItem::ItemContainsChildrenInShape, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}


void ItemGroup::setRect(QRectF rect)
{
    QPainterPath path;
    path.addRect(rect);
    setShape(path);
}


QRectF ItemGroup::renderRect() const
{
    return m_renderRect;
}

QRectF ItemGroup::rect() const
{
    return m_rect;
}

QRectF ItemGroup::boundingRect() const
{
    return renderRect();
}

void ItemGroup::addItem(AbstractItemBase *children)
{
    QPointF itemPos = children->pos();

    m_children.append(children);
    children->setParentItem(this);
    children->setVisible(false);

    if(m_children.isEmpty()) setPos(itemPos);

    QRectF rect = children->rect();
    rect.moveTopLeft(itemPos);
    m_rect = m_rect.united(rect);

    QRectF renderRect = children->renderRect();
    renderRect.moveTopLeft(itemPos);
    m_renderRect = m_renderRect.united(renderRect);



    qDebug() << "ItemGroup" << scenePos() << parentItem();
}

QList<AbstractItemBase *> ItemGroup::childItems() const
{
    return m_children;
}

void ItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(childItems().isEmpty()) return;

//    m_renderRect = rect();

    foreach(QGraphicsItem* item, childItems()){
        AbstractItemBase *abItem = dynamic_cast<AbstractItemBase*>(item);

        if(abItem){
            painter->translate(abItem->pos());
            abItem->paint(painter,option,widget);
            painter->translate(-abItem->pos());
        }
    }
}

void ItemGroup::render(QPainter *painter, qreal scale)
{

}
