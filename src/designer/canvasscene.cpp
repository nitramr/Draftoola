#include "canvasscene.h"
#include <QDebug>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QSvgGenerator>
#include <QPdfWriter>
#include "src/designer/handleframe.h"

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

/**
 * @brief [SLOT] Export all items on canvas into all provided output formats.
 */
void CanvasScene::exportItems()
{
    this->clearSelection();

    foreach(QGraphicsItem *item, this->items()){

        AbstractItemBase * aItem = dynamic_cast<AbstractItemBase*>(item);
        if(aItem){
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
                saveSVG(item, output + ".svg");
                break;
            case ExportLevel::FileFormat::PDF:
                savePDF(item, output + ".pdf");
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

    QImage image(QSizeF(bi->renderRect().width()*multiplier,bi->renderRect().height()*multiplier ).toSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(bgColor);

    QPainter painter(&image);
    painter.scale(multiplier,multiplier);
    painter.translate(bi->renderRect().topLeft().x() * -1, bi->renderRect().topLeft().y() * -1);

    bi->setHighRenderQuality(true);
    bi->render(&painter);
    bi->setHighRenderQuality(false);

    painter.end();

    image.save(outputPath, nullptr, 100);

}

/**
 * @brief Convert object as SVG and save it under given output path.
 * @param bi
 * @param multiplier
 * @param outputPath
 */
void CanvasScene::saveSVG(AbstractItemBase *bi, const QString outputPath)
{
    QRectF targetRect = bi->renderRect();

    QSvgGenerator generator;
    generator.setFileName(outputPath);
    generator.setSize(targetRect.size().toSize());  // Set the dimensions of the working area of the document in millimeters
    generator.setViewBox(targetRect);
    generator.setTitle(bi->name());
    generator.setDescription(trUtf8("File created by WhitePrint Studio"));
    generator.setResolution(72);

    QPainter painter(&generator);

    bi->setHighRenderQuality(true);
    bi->render(&painter);
    bi->setHighRenderQuality(false);

    painter.end();


}

/**
 * @brief Render object as PDF and save it under given output path.
 * @param bi
 * @param multiplier
 * @param outputPath
 */
void CanvasScene::savePDF(AbstractItemBase *bi, const QString outputPath)
{
    QPageSize pSize(QSizeF(bi->renderRect().size()).toSize());

    QPdfWriter pdfWriter(outputPath);
    pdfWriter.setPageSize(pSize);
    pdfWriter.setTitle(bi->name());
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setResolution(72);
    pdfWriter.setCreator(trUtf8("File created by WhitePrint Studio"));

    QPainter painter(&pdfWriter);
    painter.translate(bi->renderRect().topLeft().x() * -1, bi->renderRect().topLeft().y() * -1);

    bi->setHighRenderQuality(true);
    bi->render(&painter);
    bi->setHighRenderQuality(false);

    painter.end();

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


    // hover highlight
    if(!m_hoverPath.isEmpty()){

        painter->save();

        QPen highlightPen(QColor(0, 128, 255));
        highlightPen.setWidthF(2/scaleFactor());

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(highlightPen);
        painter->setBrush(Qt::NoBrush);
        painter->translate(m_hoverPoint);
        painter->drawPath(m_hoverPath);

        painter->restore();
    }


}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    m_hoverPath = QPainterPath();
    update(); // not sure if that is a performance killer

    QPoint mousePos = event->scenePos().toPoint();

    QList<QGraphicsItem*> list = this->items(mousePos,Qt::IntersectsItemShape, Qt::DescendingOrder, QTransform() );
    if(list.isEmpty()) return;

    QGraphicsItem * cgItem = list.first();

    if(cgItem->type() == HandleFrame::Type::Handle && list.count() >1){
        cgItem = list[1];
    }

    AbstractItemBase *item = dynamic_cast<AbstractItemBase*>( cgItem );

    // get hover path from item under mouse and respect item shape
    if(item ){

        if(item->shape().contains(item->mapFromScene(mousePos)) ){
            QPainterPath shape = m_hoverPath;
            m_hoverPath = item->shape();
            m_hoverPoint = item->scenePos();

            if(m_hoverPath != shape){
                update();
            }
        }
    }


}



