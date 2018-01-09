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
//	if(scaleFactor() >= 10.0){

//		const int gridSize = 1;

//		qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
//		qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

//		QVarLengthArray<QLineF, 100> lines;

//		for (qreal x = left; x < rect.right(); x += gridSize)
//			lines.append(QLineF(x, rect.top(), x, rect.bottom()));
//		for (qreal y = top; y < rect.bottom(); y += gridSize)
//			lines.append(QLineF(rect.left(), y, rect.right(), y));


//		painter->setPen(QPen(QBrush(QColor(200,200,200)),1 / scaleFactor()));
//		painter->drawLines(lines.data(), lines.size());
//	}

}



