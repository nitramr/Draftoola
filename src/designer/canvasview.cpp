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

#include "src/item/itemstruct.h"
#include "src/item/itembase.h"
#include "src/item/itemgroup.h"

#include "canvasscene.h"
#include "handleframe.h"

CanvasView::CanvasView(QWidget * parent) : QGraphicsView(parent)
{

    //    this->setRenderHint(QPainter::Antialiasing, true);
    //    this->setRenderHint( QPainter::SmoothPixmapTransform, true );
    this->setDragMode(QGraphicsView::RubberBandDrag);
    //    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setOptimizationFlag(DontAdjustForAntialiasing, true); // https://doc.qt.io/qt-5/qgraphicsview.html#OptimizationFlag-enum
    this->setOptimizationFlag(DontSavePainterState, true); // restoring painter will handle in item paint event
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // http://doc.qt.io/gt-5/qgraphicsview.html#ViewportUpdateMode-enum
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setBackgroundBrush(QColor(240,240,240));
    //    this->setRubberBandSelectionMode(Qt::ContainsItemShape);



    m_scene = new CanvasScene();
    m_scene->setSceneRect(QRectF(-4000, -4000, 8000,8000));
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    m_grid = 1;
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

    this->setLayout(gridLayout);
    this->setScene(m_scene);

    timer = new QTimer(this);
    this->connect(timer, &QTimer::timeout, this, &CanvasView::resetItemCache);
    this->connect(this, &CanvasView::rubberBandChanged, this, &CanvasView::filterSelection);

    this->connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateVRuler);
    this->connect(this->horizontalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateHRuler);

    this->connect(m_scene, SIGNAL(selectionChanged()), m_handleFrame,SLOT(frameToSelection()));

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
    foreach(QGraphicsItem *item, m_scene->items()){
        ItemBase * b_item = dynamic_cast<ItemBase*>(item);
        if(b_item){
            b_item->setCacheMode(QGraphicsItem::NoCache); // https://doc.qt.io/qt-5/qgraphicsitem.html#CacheMode-enum
            // b_item->setInvalidateCache(true);
        }
    }

}

void CanvasView::updateVRuler()
{
    qreal vPos = -mapToScene(this->rect().topLeft()).y();
    m_VRuler->setOrigin(vPos);
}

void CanvasView::updateHRuler()
{
    qreal hPos = -mapToScene(this->rect().topLeft()).x();
    m_HRuler->setOrigin(hPos);
}

/*!
 * \brief If an Artboard is fully covered it will remove all other items from selection.
 * \param viewportRect
 * \param fromScenePoint
 * \param toScenePoint
 */
void CanvasView::filterSelection(QRect viewportRect, QPointF fromScenePoint, QPointF toScenePoint )
{

    if(this->rubberBandRect().isNull()) return;

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

    QList<QGraphicsItem *> selectedItems = m_scene->items(rubberBand, Qt::IntersectsItemShape, Qt::AscendingOrder, this->transform());

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
void CanvasView::groupSelection()
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
void CanvasView::ungroupSelection()
{

}


/*!
 * \brief [SLOT] Delete selected items from canvas.
 */
void CanvasView::deleteSelection()
{
    foreach(QGraphicsItem *graphicItem, m_scene->selectedItems() ){
        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(graphicItem);
        if(abItem){
            m_scene->removeItem(abItem);
            abItem->deleteLater();
        }
    }

    emit itemsChanged();
}


void CanvasView::applyScaleFactor()
{
    qreal scaleFactor = this->scaleFactor();

    m_handleFrame->setScaleFactor(scaleFactor);
    m_scene->setScaleFactor(scaleFactor);
    m_VRuler->setScaleFactor(scaleFactor);
    m_HRuler->setScaleFactor(scaleFactor);
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

/***************************************************
 *
 * Events
 *
 ***************************************************/

void CanvasView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {

        timer->stop();
        qreal scaleX = this->scaleFactor();

        const ViewportAnchor anchor = transformationAnchor();
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        int angle = event->delta();//event->angleDelta().y();
        qreal factor = 1;

        if(angle == 0){
            factor = 1.0;
        }
        else if (angle < 0) {
            if(scaleX >= 40) return; // limit zoom level to 4000%
            factor += .2;
        }else {
            if(scaleX <= 0.1) return; // limit zoom level to 10%
            factor -= .2;
        }

        // Performance optimization by zooming
        foreach(QGraphicsItem *item, m_scene->items()){
            ItemBase * b_item = dynamic_cast<ItemBase*>(item);
            if(b_item){
                // keep the rendered item in cache while zooming. No redraw = better performance.
                b_item->setCacheMode(QGraphicsItem::ItemCoordinateCache); // https://doc.qt.io/qt-5/qgraphicsitem.html#CacheMode-enum
            }
        }

        this->scale(factor, factor);
        this->setTransformationAnchor(anchor);

        applyScaleFactor();

        timer->start(100);

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
            qDebug() << this->matrix().m11() * 100 << "%";

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
        case Qt::Key_G :
            groupSelection();
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
        deleteSelection();
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

        switch(item->type()){
        case AbstractItemBase::Rect:{
            ItemRect *rect = static_cast<ItemRect*>(item);

            if(rect){

            }
        }
            break;
        default:

            break;
        }




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

