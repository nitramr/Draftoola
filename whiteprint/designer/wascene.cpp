#include "wascene.h"
#include <QDebug>
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

WAScene::WAScene(QObject *parent) : QGraphicsScene(parent)
{

}

/***************************************************
 *
 * Slots
 *
 ***************************************************/



//void WAScene::updateItemProperties()
//{
//    QList<QGraphicsItem*> selecitems = this->selectedItems();

//    if(selectedItems().size()==1){
//        ItemBase* m_itemBase = dynamic_cast<ItemBase*>(selecitems[0]);
//        if(m_itemBase){
//            emit emitActiveItem(m_itemBase);
//        }

//    }
//}


/***************************************************
 *
 * Events
 *
 ***************************************************/


void WAScene::keyPressEvent(QKeyEvent *e)
{


	QGraphicsScene::keyPressEvent(e);
}

void WAScene::keyReleaseEvent(QKeyEvent *e)
{


	QGraphicsScene::keyReleaseEvent(e);
}

void WAScene::drawForeground(QPainter *painter, const QRectF &rect)
{


}



