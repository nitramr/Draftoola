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
    m_grid = 1;
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

/**
 * @brief [SLOT] Export all items on canvas into all provided output formats.
 */
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

/**
 * @brief [SLOT] Export single item into all provided output formats.
 * @param item
 */
void CanvasScene::exportItem(AbstractItemBase *item)
{
    if(item){

        foreach(ExportLevel expLevel, item->exportLevels()){

            double multiplier = expLevel.renderLevel();

            QString output = (expLevel.pathType() == ExportLevel::PathType::prefix)
                    ? expLevel.path() + item->name()
                    : item->name() + expLevel.path();

            switch(expLevel.fileFormat()){
            case ExportLevel::FileFormat::JPG:
                saveImage(item, multiplier, output + ".jpg", Qt::white);
                break;
            case ExportLevel::FileFormat::SVG:
                saveSVG(item, multiplier, output + ".svg");
                break;
            case ExportLevel::FileFormat::PDF:
                savePDF(item, multiplier, output + ".pdf");
                break;
            default:
            case ExportLevel::FileFormat::PNG:
                saveImage(item, multiplier, output + ".png");
                break;
            }
        }

    }
}

/**
 * @brief Render object as Image and save it under given output path.
 * @param bi
 * @param multiplier
 * @param outputPath
 */
void CanvasScene::saveImage(AbstractItemBase *bi, qreal multiplier, const QString outputPath, QColor bgColor)
{
    qDebug() << "saveImage start";

    QImage image(QSizeF(bi->renderRect().width()*multiplier,bi->renderRect().height()*multiplier ).toSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(bgColor);

    QPainter painter(&image);
    painter.scale(multiplier,multiplier);
    painter.translate(bi->renderRect().topLeft().x() * -1, bi->renderRect().topLeft().y() * -1);

    Artboard *artboard = dynamic_cast<Artboard*>(bi);

    if(artboard){
        //renderHighQuality(artboard);
        artboard->setDoRender(true);
        artboard->setHighRenderQuality(true);
        render(&painter,artboard->canvas()->rect(), artboard->canvas()->rect());
        artboard->setDoRender(false);
        artboard->setHighRenderQuality(false);
        //renderHighQuality(artboard, false);

    }else{
        bi->setHighRenderQuality(true);
        bi->render(&painter);
        bi->setHighRenderQuality(false);

    }


    painter.end();

    image.save(outputPath);

    qDebug() << "saveImage end: " + outputPath;
}

/**
 * @brief Convert object as SVG and save it under given output path.
 * @param bi
 * @param multiplier
 * @param outputPath
 */
void CanvasScene::saveSVG(AbstractItemBase *bi, qreal multiplier, const QString outputPath)
{
    // Do SVG stuff
}

/**
 * @brief Render object as PDF and save it under given output path.
 * @param bi
 * @param multiplier
 * @param outputPath
 */
void CanvasScene::savePDF(AbstractItemBase *bi, qreal multiplier, const QString outputPath)
{
    // Do PDF stuff
}

void CanvasScene::renderHighQuality(AbstractItemBase *item, bool enableQuality)
{
    if(item){
        QList<QGraphicsItem*> list = item->childItems();
        foreach(QGraphicsItem *object, list){
            AbstractItemBase *abItem = dynamic_cast<AbstractItemBase*>(object);
            if(abItem){
                abItem->setHighRenderQuality(enableQuality);
                qDebug() << "update Render Quality" << abItem->ID();
            }
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

    // draw grid
    if (scaleFactor() > 10 ) {
        // painter->setClipRect( rect);

        qreal left = int(rect.left()) - (int(rect.left()) % m_grid);
        qreal top = int(rect.top()) - (int(rect.top()) % m_grid);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += m_grid)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += m_grid)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        QPen pen(QColor(225,225,225, 128));
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawLines(lines.data(), lines.size());
    }

}



