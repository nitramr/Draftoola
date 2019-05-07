#include "canvasscene.h"
#include <QDebug>
#include <QtGlobal>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

CanvasScene::CanvasScene(QObject *parent) : QGraphicsScene(parent)
{
    m_scaleFactor = 1;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

qreal CanvasScene::scaleFactor() const
{
    return m_scaleFactor;
}

void CanvasScene::setScaleFactor(qreal factor)
{
    m_scaleFactor = factor;
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void CanvasScene::render(QPainter *painter, const QRectF &target, const QRectF &source,
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


void CanvasScene::exportItems()
{
    this->clearSelection();

    foreach(QGraphicsItem *item, this->items()){

        AbstractItemBase * aItem = dynamic_cast<AbstractItemBase*>(item);
        if(aItem){
            if(aItem->exportLevels().count() > 0)
                exportItem(aItem);
        }

    }

}

void CanvasScene::exportItem(AbstractItemBase *item)
{



    ItemBase *bi = dynamic_cast<ItemBase*>(item);
    if(bi){

        foreach(ExportLevel expLevel, item->exportLevels()){

            double multiplier = expLevel.renderLevel();

            QImage image(QSizeF(bi->boundingRect().width()*multiplier,bi->boundingRect().height()*multiplier ).toSize(), QImage::Format_ARGB32_Premultiplied);
            image.fill(Qt::transparent);

            QPainter painter(&image);
            painter.scale(multiplier,multiplier);
            painter.translate(bi->boundingRect().topLeft().x() * -1, bi->boundingRect().topLeft().y() * -1);
            //painter.setRenderHint(QPainter::HighQualityAntialiasing);
            bi->setHighRenderQuality(true);
            bi->render(&painter);
            bi->setHighRenderQuality(false);
            painter.end();

            QString output = "";
            QString fileFormat = "";

            switch(expLevel.fileFormat()){
            case ExportLevel::FileFormat::JPG:
                fileFormat = ".jpg";
                break;
            case ExportLevel::FileFormat::SVG:
                fileFormat = ".svg";
                break;
            case ExportLevel::FileFormat::PDF:
                fileFormat = ".pdf";
                break;
            default:
            case ExportLevel::FileFormat::PNG:
                fileFormat = ".png";
                break;
            }

            if(expLevel.pathType() == ExportLevel::PathType::prefix){
                output = expLevel.path() + item->name() + fileFormat;
            }else{
                output = item->name() + expLevel.path() + fileFormat;
            }

            image.save(output);
        }

    }
}

AbstractItemBase *CanvasScene::itemByName(const QString name)
{
    foreach(QGraphicsItem *item, this->items()) {
        AbstractItemBase *ibItem = dynamic_cast<AbstractItemBase*>(item);

        if(ibItem){
            if(ibItem->name() == name) return ibItem;
        }
    }

    return nullptr;
}

/***************************************************
 *
 * Events
 *
 ***************************************************/


void CanvasScene::keyPressEvent(QKeyEvent *e)
{
	QGraphicsScene::keyPressEvent(e);
}

void CanvasScene::keyReleaseEvent(QKeyEvent *e)
{
    QGraphicsScene::keyReleaseEvent(e);
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
}

void CanvasScene::drawForeground(QPainter *painter, const QRectF &rect)
{

    QGraphicsScene::drawForeground(painter, rect);


    // zoom level
    const qreal lod = scaleFactor();

    // draw grid
    if (lod > 10 ) {

        painter->setClipRect( rect);

        const int gridSize = 1;

        qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
        qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += gridSize)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += gridSize)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        QPen pen(QColor(128,128,128, 40));
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawLines(lines.data(), lines.size());
    }

}



