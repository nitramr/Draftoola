#include "canvasview.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QGraphicsItemGroup>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QTimer>
#include <QTransform>
#include <QScrollBar>
#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QtMath>

#include <itemstruct.h>
#include <artboard.h>
#include <itembase.h>
#include <itemgroup.h>
#include <itempolygon.h>
#include <itemoval.h>
#include <itemrect.h>
#include <itemtext.h>
#include <canvasscene.h>
#include <handleframe.h>

static const QString mimeType("application/canvasItem");

CanvasView::CanvasView(QWidget * parent) : QGraphicsView(parent)
{

    //    this->setRenderHint(QPainter::Antialiasing, true);
    //    this->setRenderHint( QPainter::SmoothPixmapTransform, true );
    setDragMode(QGraphicsView::RubberBandDrag);
    //    this->setCacheMode(QGraphicsView::CacheBackground);
    setOptimizationFlag(DontAdjustForAntialiasing, true); // https://doc.qt.io/qt-5/qgraphicsview.html#OptimizationFlag-enum
    setOptimizationFlag(DontSavePainterState, true); // restoring painter will handle in item paint event
    //    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // http://doc.qt.io/gt-5/qgraphicsview.html#ViewportUpdateMode-enum
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setBackgroundBrush(QColor(240,240,240));
    //    this->setRubberBandSelectionMode(Qt::ContainsItemShape);
    //    this->setMouseTracking(true);


    m_scene = new CanvasScene();
    m_scene->setSceneRect(QRectF(-16000, -16000, 32000,32000));
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    m_grid = 1;
    m_renderQuality = AbstractItemBase::Balanced;
    m_activeArtboard = nullptr;
    QColor color(0, 128, 255);

    m_handleFrame = new HandleFrame(m_scene, m_grid);
    m_handleFrame->setColor(color);
    m_scene->addItem(m_handleFrame);
    m_handleFrame->setup();

    setViewportMargins(RULER_SIZE,RULER_SIZE,0,0);

    m_HRuler = new QDRuler(QDRuler::Horizontal, this);
    m_HRuler->setMarkerColor(color);
    m_VRuler = new QDRuler(QDRuler::Vertical, this);
    m_VRuler->setMarkerColor(color);

    QWidget* fake = new QWidget();
    fake->setBackgroundRole(QPalette::Window);
    fake->setFixedSize(RULER_SIZE,RULER_SIZE);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    gridLayout->addWidget(fake,0,0);
    gridLayout->addWidget(m_HRuler,0,1);
    gridLayout->addWidget(m_VRuler,1,0);
    gridLayout->addWidget(this->viewport(),1,1);

    setLayout(gridLayout);
    setScene(m_scene);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CanvasView::resetItemCache);

    connect(this, &CanvasView::rubberBandChanged, this, &CanvasView::filterSelection);

    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateVRulerPosition);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateHRulerPosition);

    connect(m_scene, &CanvasScene::selectionChanged, m_handleFrame, &HandleFrame::frameToSelection);

    connect(m_handleFrame, &HandleFrame::geometryChanged, this, &CanvasView::setRulerToSelection);

}


HandleFrame *CanvasView::handleFrame() const
{
    return m_handleFrame;
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void CanvasView::resetItemCache()
{
    QRectF _viewFrame = mapToScene( viewport()->geometry() ).boundingRect();

    foreach(QGraphicsItem *item, m_scene->items(_viewFrame)){

        ItemBase * b_item = dynamic_cast<ItemBase*>(item);
        if(b_item){
            b_item->setRenderQuality(m_renderQuality);
            b_item->setCacheMode(QGraphicsItem::NoCache); // https://doc.qt.io/qt-5/qgraphicsitem.html#CacheMode-enum
            //b_item->setInvalidateCache(true); // needed for shadow map refresh
        }
    }

}


/*!
 * \brief Update origin position of vertical ruler.
 */
void CanvasView::updateVRulerPosition()
{
    qreal offset = (m_activeArtboard) ? m_activeArtboard->scenePos().toPoint().y() : 0;
    m_VRuler->setOrigin( -mapToScene(rect().topLeft()).y() + offset);
}


/*!
 * \brief Update origin position of horizontal ruler.
 */
void CanvasView::updateHRulerPosition()
{        
    qreal offset = (m_activeArtboard) ? m_activeArtboard->scenePos().toPoint().x() : 0;
    m_HRuler->setOrigin( -mapToScene(rect().topLeft()).x() + offset);
}


/*!
 * \brief Set ruler origin to active artboard and set item marker
 */
void CanvasView::setRulerToSelection()
{

    QRectF marker;
    QPointF offset;

    if(!m_scene->selectedItems().isEmpty()){

        // Find top level Artboard
        m_activeArtboard = getTopLevelArtboard(m_scene->selectedItems().first());

        if(m_activeArtboard){
            offset = m_handleFrame->mapToItem(m_activeArtboard, QPointF());
            marker = m_handleFrame->rect();
        }

    }else m_activeArtboard = nullptr;

    updateHRulerPosition();
    updateVRulerPosition();

    m_HRuler->setMarkerRange(offset.x() + marker.left(),
                             offset.x() + marker.right());

    m_VRuler->setMarkerRange(offset.y() + marker.top(),
                             offset.y() + marker.bottom());
}



/*!
 * \brief If an Artboard is fully covered it will remove all other items from selection.
 * \param viewportRect
 * \param fromScenePoint
 * \param toScenePoint
 */
void CanvasView::filterSelection(QRect viewportRect, QPointF fromScenePoint, QPointF toScenePoint )
{

    if(rubberBandRect().isNull()) return;

    // Based on from which direction the rubberband have been created we have to calculate TL pos differently.
    QPointF posRubberbandTL(
                (fromScenePoint.x() <= toScenePoint.x()) ? fromScenePoint.x() : toScenePoint.x(),
                (fromScenePoint.y() <= toScenePoint.y()) ? fromScenePoint.y() : toScenePoint.y()
                                                           );

    // Based on from which direction the rubberband have been created we have to calculate BR pos differently.
    QPointF posRubberbandBR(
                (toScenePoint.x() <= fromScenePoint.x()) ? fromScenePoint.x() : toScenePoint.x(),
                (toScenePoint.y() <= fromScenePoint.y()) ? fromScenePoint.y() : toScenePoint.y()
                                                           );

    QRectF rubberBand(posRubberbandTL, posRubberbandBR);

    QList<QGraphicsItem *> selectedItems = m_scene->items(rubberBand, Qt::IntersectsItemShape, Qt::AscendingOrder, transform());

    foreach(QGraphicsItem *selectedItem, selectedItems) {

        Artboard * abItem = dynamic_cast<Artboard*>(selectedItem);

        if(abItem){

            QRect itemRect = abItem->rect().toRect();
            itemRect.moveTo(abItem->scenePos().toPoint() );

            if(rubberBand.contains(itemRect) ){
                abItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            }else abItem->setFlag(QGraphicsItem::ItemIsSelectable, false);

            continue;

        }


    }

}


/***************************************************
 *
 * Member
 *
 ***************************************************/

void CanvasView::addItem(AbstractItemBase *item, qreal x, qreal y, AbstractItemBase *parent)
{

    Artboard * m_artboard = dynamic_cast<Artboard*>(item);

    if(m_artboard){ // Item is Artboard

        qDebug() << "Canvas: Item is Artboard";

        m_scene->addItem(m_artboard);
        m_artboard->setPos(x,y);

        emit itemsChanged();

    }else{ // Item is no Artboard

        qDebug() << "Canvas: Item is no Artboard";

        QList<Artboard*> abList = artboardList();

        if(parent == nullptr && abList.count() > 0){

            qDebug() << "Canvas: Item has no Parent";
            Artboard * artboard = abList.first();

            if(artboard){
                artboard->addItem(item);
                item->setPos(x,y);
                emit itemsChanged();
            }

        }else if(parent){

            qDebug() << "Canvas: Item has Parent";

            parent->addItem(item);
            item->setPos(x,y);
            emit itemsChanged();
        }

    }

}


AbstractItemBase::RenderQuality CanvasView::renderQuality() const
{
    return m_renderQuality;
}


void CanvasView::setRenderQuality(AbstractItemBase::RenderQuality renderQuality)
{
    m_renderQuality = renderQuality;
}


AbstractItemBase *CanvasView::itemByName(const QString name)
{
    foreach(QGraphicsItem *item, m_scene->items()) {
        AbstractItemBase *ibItem = dynamic_cast<AbstractItemBase*>(item);

        if(ibItem){
            if(ibItem->name() == name) return ibItem;
        }
    }

    return nullptr;
}


/*!
 * \brief Return list of all artboards on canvas.
 * \return
 */
QList<Artboard *> CanvasView::artboardList()
{
    QList<Artboard *> artboardList = QList<Artboard*>();

    foreach(QGraphicsItem *item, m_scene->items(Qt::AscendingOrder)){
        Artboard *artItem = dynamic_cast<Artboard*>(item);
        if(artItem) artboardList.append(artItem);
    }

    return artboardList;
}

/*!
 * \brief [SLOT] Create QGraphicsItemGroup out of selected items.
 */
void CanvasView::groupItems()
{
    //    QGraphicsItemGroup *grpItem = new QGraphicsItemGroup();

    //    foreach(QGraphicsItem *item, m_scene->selectedItems()){
    //        grpItem->addToGroup(item);
    //    }

    // Group all selected items together
    ItemGroup *group = createItemGroup(m_scene->selectedItems());
    //    group->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //    group->setFlag(QGraphicsItem::ItemIsMovable, true);

    // Destroy the group, and delete the group item
    // scene->destroyItemGroup(group);
}


/*!
 * \brief [SLOT] Destroy selected QGraphicsItemGroup into single items.
 */
void CanvasView::ungroupItems()
{

}


/*!
 * \brief [SLOT] Delete selected items from canvas.
 */
void CanvasView::deleteItems()
{
    foreach(QGraphicsItem *graphicItem, m_scene->selectedItems() ){
        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(graphicItem);
        if(abItem){
            m_scene->removeItem(abItem);
            abItem->deleteLater();
        }
    }

    m_scene->clearSelection();

    emit itemsChanged();
}

void CanvasView::pasteItems()
{
    //    if(m_copyCache.isEmpty()) return;

    //    // find artboard under mouse
    //    // if artboard contain in cache add it to scene
    //    foreach(AbstractItemBase *abItem, m_copyCache ){
    //        addItem(abItem);
    //    }



    QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();

    QStringList formats = mimeData->formats();
    foreach (QString format, formats)
    {
        if (format == mimeType)
        {
            QByteArray itemData = mimeData->data(mimeType);
            QDataStream inData(&itemData, QIODevice::ReadOnly);
            int itemsSize;
            inData >> itemsSize;
            for (int i = 0; i < itemsSize; ++i)
            {
                //                    AbstractItemBase* item = ...
                //                    item->loadItem(inData);
            }
        }
    }

}


void CanvasView::copyItems(bool asDuplicate)
{
    m_copyCache.clear();

    // TODO: add all children to cache too
    // Reference: https://stackoverflow.com/questions/32980629/how-to-implement-clipboard-actions-for-custom-mime-types

    //    foreach(QGraphicsItem *graphicItem, m_scene->selectedItems() ){
    //        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(graphicItem);
    //        if(abItem){
    //            switch(abItem->type()){
    //            case AbstractItemBase::Artboard:
    //                m_copyCache.append(new Artboard(*dynamic_cast<Artboard*>(abItem)) );
    //                break;
    //            case AbstractItemBase::Oval:{
    //                ItemOval *oval = new ItemOval(*dynamic_cast<ItemOval*>(abItem));
    //                if(!asDuplicate){
    //                    //oval->setParentItem(nullptr);
    //                    m_scene->removeItem(oval);
    //                }
    //                m_copyCache.append(oval );
    //                break;
    //            }
    //            case AbstractItemBase::Path:
    //                break;
    //            case AbstractItemBase::Rect:
    //                m_copyCache.append(new ItemRect(*dynamic_cast<ItemRect*>(abItem)) );
    //                break;
    //            case AbstractItemBase::Polygon:
    //                m_copyCache.append(new ItemPolygon(*dynamic_cast<ItemPolygon*>(abItem)) );
    //                break;
    //            case AbstractItemBase::Instance:
    //                break;
    //            case AbstractItemBase::Line:
    //                break;
    //            case AbstractItemBase::Text:
    //                m_copyCache.append(new ItemText(*dynamic_cast<ItemText*>(abItem)) );
    //                break;
    //            case AbstractItemBase::Group:
    //                break;
    //            default:
    //                break;
    //            }
    //        }
    //    }

    //    qDebug() << m_copyCache.size();


    QByteArray itemData;
    QDataStream outData(&itemData, QIODevice::WriteOnly);
    outData << m_scene->selectedItems().size();
    foreach(QGraphicsItem* qItem, m_scene->selectedItems())
    {
        AbstractItemBase* item = dynamic_cast<AbstractItemBase*>(qItem);
        //item->saveItem(outData);
        outData << item;
    }

    QMimeData* mimeData = new QMimeData;
    mimeData->setData(mimeType, itemData);
    mimeData->setText("Canvas Item");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->clear();
    clipboard->setMimeData(mimeData);

    qDebug() << clipboard->mimeData();

    // if duplicate paste directly
    if(asDuplicate) pasteItems();

}


void CanvasView::applyScaleFactor()
{
    qreal scaleFactor = this->scaleFactor();

    m_handleFrame->setScaleFactor(scaleFactor);
    m_scene->setScaleFactor(scaleFactor);
    m_VRuler->setScaleFactor(scaleFactor);
    m_HRuler->setScaleFactor(scaleFactor);

    emit zoomChanged(scaleFactor);
}


qreal CanvasView::scaleFactor() const
{
    return this->matrix().m11();
}


ItemGroup *CanvasView::createItemGroup(const QList<QGraphicsItem *> &items)
{
    // Build a list of the first item's ancestors
    QList<QGraphicsItem *> ancestors;
    int n = 0;
    if (!items.isEmpty()) {
        QGraphicsItem *parent = items.at(n++);
        while ((parent = parent->parentItem()))
            ancestors.append(parent);
    }
    // Find the common ancestor for all items
    QGraphicsItem *commonAncestor = 0;
    if (!ancestors.isEmpty()) {
        while (n < items.size()) {
            int commonIndex = -1;
            QGraphicsItem *parent = items.at(n++);
            do {
                int index = ancestors.indexOf(parent, qMax(0, commonIndex));
                if (index != -1) {
                    commonIndex = index;
                    break;
                }
            } while ((parent = parent->parentItem()));
            if (commonIndex == -1) {
                commonAncestor = 0;
                break;
            }
            commonAncestor = ancestors.at(commonIndex);
        }
    }
    // Create a new group at that level
    ItemGroup *group = new ItemGroup(commonAncestor);
    if (!commonAncestor)
        m_scene->addItem(group);
    for (QGraphicsItem *item : items){
        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(item);
        if(abItem) group->addItem(abItem);
    }

    return group;
}

Artboard *CanvasView::getTopLevelArtboard(QGraphicsItem *item)
{
    if(!item) return nullptr;

    Artboard *artboard = dynamic_cast<Artboard*>(item->topLevelItem());
    return (artboard) ? artboard : nullptr;

}

/***************************************************
 *
 * Events
 *
 ***************************************************/

void CanvasView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {

        qreal scaleX = this->scaleFactor();

        bool isZoomed = (scaleX > 1.0) ? true : false;

        if(isZoomed) timer->stop();

        const ViewportAnchor anchor = transformationAnchor();
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        int angle = event->delta();//event->angleDelta().y();
        qreal factor = 1;

        if(angle == 0){
            factor = 1.0;
        }
        else if (angle < 0) {
            if(scaleX >= 50) return; // limit zoom level to 5000%
            factor += .2;
        }else {
            if(scaleX <= 0.1) return; // limit zoom level to 10%
            factor -= .2;
        }


        // Performance optimization by zooming
        if(isZoomed) {
            QRectF _viewFrame = this->mapToScene( this->viewport()->geometry() ).boundingRect();
            foreach(QGraphicsItem *item, m_scene->items(_viewFrame)){
                ItemBase * b_item = dynamic_cast<ItemBase*>(item);
                if(b_item){
                    // keep the rendered item in cache while zooming. No redraw = better performance.
                    if(b_item->cacheMode() != QGraphicsItem::ItemCoordinateCache) b_item->setCacheMode(QGraphicsItem::ItemCoordinateCache); // https://doc.qt.io/qt-5/qgraphicsitem.html#CacheMode-enum
                }
            }
        }

        this->scale(factor, factor);
        this->setTransformationAnchor(anchor);

        applyScaleFactor();

        if(isZoomed) timer->start(200);

    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void CanvasView::keyPressEvent(QKeyEvent *event)
{

    qreal stepperS = 1.0;
    qreal stepperL = 9.0;

    // Single Key + Ctrl
    if (event->modifiers() & Qt::CTRL) {
        switch(event->key())
        {
        case Qt::Key_0 :

            this->resetMatrix();
            applyScaleFactor();

            break;
        case Qt::Key_1 :

            this->scale(2, 2);
            applyScaleFactor();

            break;
        }

    }

    // Single Key + Shift
    if (event->modifiers() & Qt::ShiftModifier) {
        switch(event->key())
        {
        case Qt::Key_Left :
            m_handleFrame->moveBy(-stepperL, 0);

            break;
        case Qt::Key_Right :
            m_handleFrame->moveBy(stepperL, 0);

            break;
        case Qt::Key_Up :
            m_handleFrame->moveBy(0, -stepperL);

            break;
        case Qt::Key_Down :
            m_handleFrame->moveBy(0, stepperL);

            break;
        }
    }

    // Single Key
    switch(event->key())
    {
    case Qt::Key_Left :
        m_handleFrame->moveBy(-stepperS, 0);

        break;
    case Qt::Key_Right :
        m_handleFrame->moveBy(stepperS, 0);

        break;
    case Qt::Key_Up :
        m_handleFrame->moveBy(0, -stepperS);

        break;
    case Qt::Key_Down :
        m_handleFrame->moveBy(0, stepperS);

        break;
    case Qt::Key_Shift :
        m_handleFrame->setKeepAspectRatio(true);

        break;
    case Qt::Key_Space:
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        this->setInteractive(false);

        break;

    }


    //	QGraphicsView::keyPressEvent(e);
}

void CanvasView::keyReleaseEvent(QKeyEvent *event)
{
    // Single Key + Ctrl
    if (event->modifiers() & Qt::CTRL) {
        switch(event->key())
        {
        case Qt::Key_C :
            copyItems(false);
            break;
        case Qt::Key_D :
            copyItems(true);
            break;
        case Qt::Key_G :
            groupItems();
            break;
        case Qt::Key_V:
            pasteItems();
            break;
        }

    }

    // Single Key
    switch(event->key())
    {
    case Qt::Key_Space :
        this->setDragMode(QGraphicsView::RubberBandDrag);
        this->setInteractive(true);
        break;
    case Qt::Key_Shift :
        m_handleFrame->setKeepAspectRatio(false);
        break;
    case Qt::Key_Delete:
        deleteItems();
        break;

        // Tmp functions
    case Qt::Key_A:{

        m_scene->clearSelection();

        AbstractItemBase *item = itemByName("Rect1");


        QPointF init = item->pos();

        QPropertyAnimation *animation = new QPropertyAnimation(item, "pos");
        animation->setDuration(1000);
        animation->setEasingCurve(QEasingCurve::InBack);
        animation->setStartValue(init);
        animation->setKeyValueAt(0.5, QPointF(30,100));
        animation->setEndValue(init);

        animation->start();

        break;
    }
    case Qt::Key_V:{
        m_scene->exportItems();
        break;
    }

    }


    QGraphicsView::keyReleaseEvent(event);
}

void CanvasView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    // Ruler
    m_HRuler->setCursorPos(event->screenPos().toPoint()/* -QPoint(RULER_BREADTH, RULER_BREADTH)*/);
    m_VRuler->setCursorPos(event->screenPos().toPoint()/* -QPoint(RULER_BREADTH, RULER_BREADTH)*/);

}

void CanvasView::mousePressEvent(QMouseEvent *event)
{

    QGraphicsView::mousePressEvent(event);

}

void CanvasView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);



}

