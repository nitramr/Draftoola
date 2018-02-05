#include "wascene.h"
#include <QDebug>


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

void WAScene::render(QPainter *painter, const QRectF &target, const QRectF &source,
								Qt::AspectRatioMode aspectRatioMode)
	{

	QGraphicsScene::render(painter,target,source,aspectRatioMode);

//		// ### Switch to using the recursive rendering algorithm instead.

//		// Default source rect = scene rect
//		QRectF sourceRect = source;
//		if (sourceRect.isNull())
//			sourceRect = sceneRect();

//		// Default target rect = device rect
//		QRectF targetRect = target;
//		if (targetRect.isNull()) {
//			if (painter->device()->devType() == QInternal::Picture)
//				targetRect = sourceRect;
//			else
//				targetRect.setRect(0, 0, painter->device()->width(), painter->device()->height());
//		}

//		// Find the ideal x / y scaling ratio to fit \a source into \a target.
//		qreal xratio = targetRect.width() / sourceRect.width();
//		qreal yratio = targetRect.height() / sourceRect.height();

//		// Scale according to the aspect ratio mode.
//		switch (aspectRatioMode) {
//		case Qt::KeepAspectRatio:
//			xratio = yratio = qMin(xratio, yratio);
//			break;
//		case Qt::KeepAspectRatioByExpanding:
//			xratio = yratio = qMax(xratio, yratio);
//			break;
//		case Qt::IgnoreAspectRatio:
//			break;
//		}

//		// Find all items to draw, and reverse the list (we want to draw
//		// in reverse order).
//		QList<QGraphicsItem *> itemList = items(sourceRect, Qt::IntersectsItemBoundingRect);
//		QGraphicsItem **itemArray = new QGraphicsItem *[itemList.size()];
//		int numItems = itemList.size();
//		for (int i = 0; i < numItems; ++i)
//			itemArray[numItems - i - 1] = itemList.at(i);
//		itemList.clear();

//		painter->save();

//		// Transform the painter.
//		painter->setClipRect(targetRect, Qt::IntersectClip);
//		QTransform painterTransform;
//		painterTransform *= QTransform()
//							.translate(targetRect.left(), targetRect.top())
//							.scale(xratio, yratio)
//							.translate(-sourceRect.left(), -sourceRect.top());
//		painter->setWorldTransform(painterTransform, true);

//		// Generate the style options
//		QStyleOptionGraphicsItem *styleOptionArray = new QStyleOptionGraphicsItem[numItems];
////		for (int i = 0; i < numItems; ++i)
////			itemArray[i]->d_ptr->initStyleOption(&styleOptionArray[i], painterTransform, targetRect.toRect());

//		// Render the scene.
////		drawBackground(painter, sourceRect);
//		drawItems(painter, numItems, itemArray, styleOptionArray);
////		drawForeground(painter, sourceRect);

//		delete [] itemArray;
//		delete [] styleOptionArray;

	//		painter->restore();
}

ItemBase *WAScene::itemByName(const QString name)
{
	foreach(QGraphicsItem *item, this->items()) {
		ItemBase *ibItem = dynamic_cast<ItemBase*>(item);

		if(ibItem){
			if(ibItem->name() == name) return ibItem;
		}
	}

	return NULL;
}


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



