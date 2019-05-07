#include "canvasview.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QTimer>
#include <QTransform>
#include <QScrollBar>
#include <QSvgGenerator>

#include "src/item/itemstruct.h"
#include "src/item/itembase.h"

#include "canvasscene.h"
#include "handleframe.h"

CanvasView::CanvasView(QWidget * parent) : QGraphicsView(parent)
{

//    this->setRenderHint(QPainter::Antialiasing, true);
//    this->setRenderHint( QPainter::SmoothPixmapTransform, true );
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setOptimizationFlag(DontAdjustForAntialiasing, true); // http://doc.qt.io/archives/qt-4.8/qgraphicsview.html#OptimizationFlag-enum
//    this->setOptimizationFlag(DontSavePainterState, true);
    this->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate); // http://doc.qt.io/archives/qt-4.8/qgraphicsview.html#ViewportUpdateMode-enum
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setBackgroundBrush(QColor(240,240,240));
    //    this->setRubberBandSelectionMode(Qt::ContainsItemShape);


    m_scene = new CanvasScene();
    m_scene->setSceneRect(QRectF(-2000, -2000, 4000,4000));
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    this->setScene(m_scene);

    m_grid = 1;
    m_artboardList = new QMap<QString, Artboard*>();
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


    timer = new QTimer(this);
    this->connect(timer, &QTimer::timeout, this, &CanvasView::resetItemCache);

    this->connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateVRuler);
    this->connect(this->horizontalScrollBar(), &QScrollBar::valueChanged, this, &CanvasView::updateHRuler);

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
            b_item->setCacheMode(QGraphicsItem::NoCache); // http://doc.qt.io/archives/qt-4.8/qgraphicsitem.html#CacheMode-enum
           // b_item->setInvalidateCache(true);
        }
    }

}

void CanvasView::updateVRuler()
{
     m_VRuler->setOrigin(-mapToScene(this->rect().topLeft()).y());
}

void CanvasView::updateHRuler()
{
     m_HRuler->setOrigin(-mapToScene(this->rect().topLeft()).x());
}

/***************************************************
 *
 * Member
 *
 ***************************************************/

void CanvasView::addItem(AbstractItemBase *item, qreal x, qreal y, QGraphicsItem *parent)
{

    Artboard * m_artboard = dynamic_cast<Artboard*>(item);

    if(m_artboard){ // Item is Artboard

        qDebug() << "Canvas: Item is Artboard";

        m_scene->addItem(m_artboard);
        m_artboardList->insert(m_artboard->name(), m_artboard);
        m_artboard->setPos(x,y);

        qDebug() << "Canvas: Artboard added";

    }else{ // Item is no Artboard

        qDebug() << "Canvas: Item is no Artboard";

        if(parent == nullptr && m_artboardList->count() > 0){

            qDebug() << "Canvas: Item has no Parent";
            Artboard * artboard = m_artboardList->first();

            if(artboard){
                //item->setParentItem(artboard->canvas());
                artboard->addItem(item);
                item->setPos(x,y);
                qDebug() << "Canvas: add Item to Artboard";
            }

        }else if(parent){

            qDebug() << "Canvas: Item has Parent";

            item->setParentItem(parent);
            item->setPos(x,y);
            qDebug() << "Canvas: add Item to Parent";
        }

    }
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
                b_item->setCacheMode(QGraphicsItem::ItemCoordinateCache); // http://doc.qt.io/archives/qt-4.8/qgraphicsitem.html#CacheMode-enum
               // b_item->setInvalidateCache(false);
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
        m_handleFrame->setShiftModifier(true);
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
    switch(event->key())
    {
    case Qt::Key_Space :
        this->setDragMode(QGraphicsView::RubberBandDrag);
        this->setInteractive(true);
        break;

    case Qt::Key_Shift :
        m_handleFrame->setShiftModifier(false);
        break;

    case Qt::Key_A:{

        AbstractItemBase *item = m_scene->itemByName("Rect1");


        QPointF init = item->pos();

        QPropertyAnimation *animation = new QPropertyAnimation(item, "pos");
        animation->setDuration(1000);
        animation->setEasingCurve(QEasingCurve::InBack);
        animation->setStartValue(init);
        animation->setKeyValueAt(0.5, QPointF(30,100));
        animation->setEndValue(init);

        animation->start();

        switch(item->itemType()){
        case ItemType::Rect:{
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

        //        m_scene->clearSelection();
        //        qreal exFactor = 4;
        //        QRectF targetRect = QRectF(10,10,60*exFactor,100*exFactor);
        //        QRectF sourceRect = QRectF(10,10,60,100);
        //        QImage image(QSize(targetRect.width(), targetRect.height()), QImage::Format_ARGB32_Premultiplied);
        //        image.fill(Qt::transparent);

        //        QPainter painter(&image);
        //        //painter.setRenderHint(QPainter::HighQualityAntialiasing);
        //        m_scene->render(&painter, targetRect, sourceRect);
        //        painter.end();

        //        image.save("file_name.png");


        m_scene->exportItems();


        //        QSvgGenerator generator;        // Create a file generator object
        //        generator.setFileName("file_name.svg");    // We set the path to the file where to save vector graphics
        //        generator.setSize(targetRect.size().toSize());  // Set the dimensions of the working area of the document in millimeters
        //        generator.setViewBox(targetRect); // Set the work area in the coordinates
        //        generator.setTitle(trUtf8("SVG Example"));                          // The title document
        //        generator.setDescription(trUtf8("File created by WhitePrint Studio"));

        //        QPainter painterSVG;
        //        painterSVG.begin(&generator);
        //        m_scene->render(&painterSVG,targetRect, sourceRect);
        //        painterSVG.end();

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

