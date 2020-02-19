/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "canvasscene.h"
#include <QDebug>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QSvgGenerator>
#include <QPdfWriter>

#include <QCoreApplication>
#include <handleframe.h>

//#include <QGraphicsItemGroup>
//#include <QGraphicsDropShadowEffect>



/***************************************************
 *
 * Constructor
 *
 ***************************************************/

CanvasScene::CanvasScene(QObject *parent) : QGraphicsScene(parent)
{
    m_scaleFactor = 1;
    m_grid = 1;

    m_color = QColor(0, 128, 255);

    m_handleFrame = new HandleFrame(this, m_grid);
    m_handleFrame->setColor(m_color);
    addItem(m_handleFrame);
    m_handleFrame->setup();

    connect(this, &CanvasScene::selectionChanged, m_handleFrame, &HandleFrame::frameToSelection);
    connect(m_handleFrame, &HandleFrame::geometryChanged, this, &CanvasScene::updateLabels);
}

HandleFrame *CanvasScene::handleFrame()
{
    return m_handleFrame;
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

/*!
 * \brief [SLOT] Export all items on canvas into all provided output formats.
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

/*!
 * \brief [SLOT] Export single item into all provided output formats.
 * \param item
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

void CanvasScene::updateLabels()
{

}


/*!
 * \brief Render object as Image and save it under given output path.
 * \param bi
 * \param multiplier
 * \param outputPath
 */
void CanvasScene::saveImage(AbstractItemBase *bi, qreal multiplier, const QString outputPath, QColor bgColor)
{

    QImage image(QSizeF(bi->renderRect().width()*multiplier,bi->renderRect().height()*multiplier ).toSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(bgColor);

    QPainter painter(&image);
    painter.scale(multiplier,multiplier);
    painter.translate(bi->renderRect().topLeft().x() * -1, bi->renderRect().topLeft().y() * -1);
    bi->render(&painter);
    painter.end();

    image.save(outputPath, nullptr, 100);

}

/*!
 * \brief Convert object as SVG and save it under given output path.
 * \param bi
 * \param outputPath
 */
void CanvasScene::saveSVG(AbstractItemBase *bi, const QString outputPath)
{
    QRectF targetRect = bi->renderRect();

    QSvgGenerator generator;
    generator.setFileName(outputPath);
    generator.setSize(targetRect.size().toSize());  // Set the dimensions of the working area of the document in millimeters
    generator.setViewBox(targetRect);
    generator.setTitle(bi->name());
    generator.setDescription(tr("File created by ") + QCoreApplication::applicationName() );
    generator.setResolution(72);

    QPainter painter(&generator);

    AbstractItemBase::RenderQuality renderQuality = bi->renderQuality();

    bi->setRenderQuality(AbstractItemBase::Quality);
    bi->render(&painter);
    bi->setRenderQuality(renderQuality);

    painter.end();


}

/*!
 * \brief Render object as PDF and save it under given output path.
 * \param bi
 * \param outputPath
 */
void CanvasScene::savePDF(AbstractItemBase *bi, const QString outputPath)
{
    QPageSize pSize(QSizeF(bi->renderRect().size()).toSize());

    QPdfWriter pdfWriter(outputPath);
    pdfWriter.setPageSize(pSize);
    pdfWriter.setTitle(bi->name());
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setResolution(72);
    pdfWriter.setCreator(tr("File created by ") + QCoreApplication::applicationName() );

    QPainter painter(&pdfWriter);
    painter.translate(bi->renderRect().topLeft().x() * -1, bi->renderRect().topLeft().y() * -1);

    AbstractItemBase::RenderQuality renderQuality = bi->renderQuality();

    bi->setRenderQuality(AbstractItemBase::Quality);
    bi->render(&painter);
    bi->setRenderQuality(renderQuality);

    painter.end();

}

/***************************************************
 *
 * Events
 *
 ***************************************************/


void CanvasScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
}

void CanvasScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
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


//    // hover highlight
//    if(!m_hoverPath.isEmpty()){
//        painter->save();
//        QPen highlightPen(m_color);
//        highlightPen.setWidthF(2/scaleFactor());

//        painter->setRenderHint(QPainter::Antialiasing, true);
//        painter->setPen(highlightPen);
//        painter->setBrush(Qt::NoBrush);
//        painter->translate(m_hoverPoint -QPointF(m_hoverTransform.dx(), m_hoverTransform.dy()) );
//        painter->drawPath( m_hoverPath /*m_hoverTransform.map(m_hoverPath)*/ );
//        painter->restore();
//    }


}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    QGraphicsScene::mouseMoveEvent(event);

//    QPoint mousePos = event->scenePos().toPoint();

//    QList<QGraphicsItem*> list = this->items(mousePos,Qt::IntersectsItemShape, Qt::DescendingOrder, QTransform() );

//    if(m_hoverPath != QPainterPath()){
//        m_hoverPath = QPainterPath();
//        invalidate(QRectF(), QGraphicsScene::ForegroundLayer);
//    }

//    if(list.isEmpty()) return;

//    QGraphicsItem * cgItem = list.first();

//    if(cgItem->type() == HandleFrame::Type::Handle && list.count() >1){
//        cgItem = list[1]; // skip handleFrame
//    }

//    if(cgItem->type() == ArtboardCanvas::Type::Canvas){
//        Artboard * artboard = dynamic_cast<Artboard*>(cgItem->parentItem());
//        if(artboard && cgItem->childItems().isEmpty()){
//            cgItem = cgItem->parentItem(); // get Artboard instead of canvas
//        }

//    }

//    AbstractItemBase * item = dynamic_cast<AbstractItemBase*>(cgItem);

//    if(item){

//        if(item->shape().contains(item->mapFromScene(mousePos)) ){
//            QPainterPath shape = m_hoverPath;
//            m_hoverPath = item->transformedPath();//item->shape();
//            m_hoverPoint = item->scenePos();
//            m_hoverTransform = item->transform();

//            if(m_hoverPath != shape){
//                invalidate(QRectF(), QGraphicsScene::ForegroundLayer);
//            }
//        }
//    }

}



