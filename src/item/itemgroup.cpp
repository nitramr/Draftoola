#include <QDebug>
#include "itemgroup.h"
#include "itemoval.h"
#include "itemrect.h"
#include "itemtext.h"

ItemGroup::ItemGroup(QGraphicsItem *parent) : ItemBase(QRectF(), parent){}

//QRectF WAGroup::rect() const
//{

//			QRectF selectionBoundingRect;
//			QList<QGraphicsItem *> selectedItems = childItems();
//			foreach(QGraphicsItem *current, selectedItems) {

//				WARect * warect = dynamic_cast<WARect*>(current);
//				WAOval * waoval = dynamic_cast<WAOval*>(current);
//				WAText * watext = dynamic_cast<WAText*>(current);
//				WAGroup * wagroup = dynamic_cast<WAGroup*>(current);

//				if(watext){
//					selectionBoundingRect = selectionBoundingRect.united(QRectF(watext->scenePos().x(), watext->scenePos().y(), watext->rect().width(), watext->rect().height()));
//				}
//				if(warect){
//					selectionBoundingRect = selectionBoundingRect.united(QRectF(warect->scenePos().x(), warect->scenePos().y(), warect->rect().width(), warect->rect().height()));
//				}
//				if(waoval){
//					selectionBoundingRect = selectionBoundingRect.united(QRectF(waoval->scenePos().x(), waoval->scenePos().y(), waoval->rect().width(), waoval->rect().height()));
//				}
//				if(wagroup){
//					selectionBoundingRect = selectionBoundingRect.united(QRectF(wagroup->scenePos().x(), wagroup->scenePos().y(), wagroup->rect().width(), wagroup->rect().height()));
//				}

//			}

//			return selectionBoundingRect;
//}

void ItemGroup::setRect(QRectF rect)
{
    QPainterPath path;
    path.addRect(rect);
    setShape(path);
}
