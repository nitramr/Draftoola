#include "handleframe.h"

#include <QDebug>
#include <QtMath>

#include "canvasscene.h"

ItemHandle::ItemHandle(QGraphicsItem *parent,  Handle corner, int handleSize, QColor color, Style style) :
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0),
    m_Pen(),
    m_corner(corner),
    m_style(style),
    m_mouseButtonState(kMouseReleased)
{
    m_handleSize = handleSize;
    m_width = m_handleSize;
    m_height = m_handleSize;

    m_Pen.setCosmetic(true);
    setColor(color);

    QGraphicsDropShadowEffect *m_shadow = new QGraphicsDropShadowEffect();
    m_shadow->setOffset(0,0);
    m_shadow->setColor(QColor(0,0,0));
    m_shadow->setBlurRadius(4);
    this->setGraphicsEffect(m_shadow);

    this->setAcceptHoverEvents(true);
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void ItemHandle::setMouseState(int s)
{
    m_mouseButtonState = s;
}


int ItemHandle::getMouseState()
{
    return m_mouseButtonState;
}


QRectF ItemHandle::rect() const
{
    return QRectF(0, 0, m_width, m_height);
}


void ItemHandle::setRect(qreal width)
{    
    if (m_width != width)
    {
        m_width = width;
        m_height = width;
        update();
    }
}


void ItemHandle::setColor(const QColor color)
{
    if (m_color != color)
    {
        m_color = color;
        m_Pen.setColor(m_color);
        update();
    }
}


QColor ItemHandle::color() const
{
    return m_color;
}


QRectF ItemHandle::boundingRect() const
{
    return rect();
}


ItemHandle::Handle ItemHandle::getCorner()
{
    return m_corner;
}

/***************************************************
 *
 * Events
 *
 ***************************************************/

//void ItemHandle::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
//{
//    event->setAccepted(false);
//}


//void ItemHandle::mousePressEvent(QGraphicsSceneDragDropEvent *event)
//{
//    event->setAccepted(false);
//}


//void ItemHandle::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
//{
//    event->setAccepted(true);
//}


void ItemHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);

    switch (m_corner) {
    case TopLeft:
    case BottomRight:
        this->setCursor(Qt::SizeFDiagCursor);
        break;
    case Top:
    case Bottom:
        this->setCursor(Qt::SizeVerCursor);
        break;
    case TopRight:
    case BottomLeft:
        this->setCursor(Qt::SizeBDiagCursor);
        break;
    case Left:
    case Right:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case Rotate:
        this->setCursor(Qt::ClosedHandCursor);
        break;
    default:
        break;
    }
}


//void ItemHandle::mousePressEvent ( QGraphicsSceneMouseEvent * event )
//{
//    event->setAccepted(false);
//}


//void ItemHandle::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
//{
//    event->setAccepted(false);
//}


void ItemHandle::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->save();
    painter->setPen(m_Pen);
    painter->setBrush(QBrush(Qt::white));
    switch(m_style){
    case Style::Square:
        painter->drawRect(this->rect());
        break;
    case Style::Round:
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawEllipse(this->rect());
        break;
    }

    painter->restore();

}

/*******************************************************************************************************************************/

/*******************************
 *
 * Handle Frame
 *
 *******************************/

HandleFrame::HandleFrame(CanvasScene *scene, qreal grid, int handleSize): QObject(), QGraphicsItem(),
    m_scene(scene),
    m_dragStart(0,0),
    m_gridSpace(grid),
    m_cornerDragStart(0,0),
    m_handleSize(handleSize),
    m_keepAspectRatio(false),
    m_pen(QPen()),
    m_scaleFactor(1.0),
    m_rect(QRectF(0,0,10,10)),
    m_ratio(1.0),
    m_canHeightChange(true),
    m_canWidthChange(true),
    m_color(QColor(0, 128, 255)),
    m_canRotate(true)
{

    m_handles[0] = new ItemHandle(this,ItemHandle::TopLeft, m_handleSize, m_color);
    m_handles[1] = new ItemHandle(this,ItemHandle::Top, m_handleSize, m_color);
    m_handles[2] = new ItemHandle(this,ItemHandle::TopRight, m_handleSize, m_color);
    m_handles[3] = new ItemHandle(this,ItemHandle::Right, m_handleSize, m_color);
    m_handles[4] = new ItemHandle(this,ItemHandle::BottomRight, m_handleSize, m_color);
    m_handles[5] = new ItemHandle(this,ItemHandle::Bottom, m_handleSize, m_color);
    m_handles[6] = new ItemHandle(this,ItemHandle::BottomLeft, m_handleSize, m_color);
    m_handles[7] = new ItemHandle(this,ItemHandle::Left, m_handleSize,m_color);
    m_handles[8] = new ItemHandle(this,ItemHandle::Rotate, m_handleSize, m_color, ItemHandle::Round);

    m_isHovered = false;
    m_rotationHandleDistance = m_handleSize * 3;

    this->setPen(QPen(m_color));
    this->setVisible(false);
    this->setAcceptHoverEvents(true);
    this->setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren, true);
//    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
//    this->setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent, true);

    this->setZValue(99999999);



}

void HandleFrame::setup(){
    m_handles[0]->installSceneEventFilter(this);
    m_handles[1]->installSceneEventFilter(this);
    m_handles[2]->installSceneEventFilter(this);
    m_handles[3]->installSceneEventFilter(this);
    m_handles[4]->installSceneEventFilter(this);
    m_handles[5]->installSceneEventFilter(this);
    m_handles[6]->installSceneEventFilter(this);
    m_handles[7]->installSceneEventFilter(this);
    m_handles[8]->installSceneEventFilter(this);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/



QRectF HandleFrame::boundingRect() const
{
    return rect().adjusted( -handleSize() / scaleFactor(),
                            -(m_rotationHandleDistance + handleSize()) / scaleFactor(),
                            handleSize() / scaleFactor(),
                            handleSize() / scaleFactor()
                            );
}

/*!
 * \brief Return an adjusted rect that fix rect position on half pixels
 * \return
 */
QRectF HandleFrame::adjustedRect() const
{
    return QRectF(rect().x() + 0.5, rect().y() + 0.5, rect().width() - 1, rect().height() - 1);
}


/*!
 * \brief Calculate BoundingRect of selected items
 * \return
 */
QRectF HandleFrame::selectionRect() const
{

    QRectF selectionRect;

    foreach(AbstractItemBase *item, m_items) {
        selectionRect = selectionRect.united(item->mapRectToScene(item->rect()));
    }

    return selectionRect;
}

void HandleFrame::moveBy(qreal dx, qreal dy)
{

    dx = (static_cast<int>(dx) / m_gridSpace) * m_gridSpace;
    dy = (static_cast<int>(dy) / m_gridSpace) * m_gridSpace;

    QGraphicsItem::moveBy(dx,dy);

    foreach(AbstractItemBase* item, m_items) {
        item->moveBy(dx,dy);
    }

    emit sendActiveItems(m_items);

}


void HandleFrame::setRect(QRectF rect)
{
    m_rect = rect;
}


void HandleFrame::setRect(qreal x, qreal y, qreal width, qreal height)
{
    setRect(QRectF(x,y,width, height));
}


QRectF HandleFrame::rect() const
{
    return m_rect;
}


qreal HandleFrame::width() const
{
    return this->rect().width();
}


qreal HandleFrame::height() const
{
    return this->rect().height();
}


QPointF HandleFrame::anchorTopLeft() const
{
    return this->scenePos();
}


QPointF HandleFrame::anchorTop() const
{
    return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y());
}


QPointF HandleFrame::anchorTopRight() const
{
    return QPointF(this->scenePos().x() + width(), this->scenePos().y());
}


QPointF HandleFrame::anchorRight() const
{
    return QPointF(this->scenePos().x() + width(), this->scenePos().y() + height() / 2);
}


QPointF HandleFrame::anchorBottomRight() const
{
    return QPointF(this->scenePos().x() + width(), this->scenePos().y() + height());
}


QPointF HandleFrame::anchorBottom() const
{
    return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y() + height());
}


QPointF HandleFrame::anchorBottomLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + height());
}


QPointF HandleFrame::anchorLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + height() / 2);
}


QPointF HandleFrame::anchorCenter() const
{
    return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y() + height() / 2);
}


void HandleFrame::setPen(QPen pen)
{
    m_pen = pen;
    m_pen.setCosmetic(true);
}


QPen HandleFrame::pen() const{
    return m_pen;
}


void HandleFrame::setScaleFactor(qreal factor)
{
    m_scaleFactor = factor;

    m_handles[0]->setRect(m_handleSize / m_scaleFactor); // TopLeft
    m_handles[1]->setRect(m_handleSize / m_scaleFactor); // Top
    m_handles[2]->setRect(m_handleSize / m_scaleFactor); // TopRight
    m_handles[3]->setRect(m_handleSize / m_scaleFactor); // Right
    m_handles[4]->setRect(m_handleSize / m_scaleFactor); // BottomRight
    m_handles[5]->setRect(m_handleSize / m_scaleFactor); // Bottom
    m_handles[6]->setRect(m_handleSize / m_scaleFactor); // BottomLeft
    m_handles[7]->setRect(m_handleSize / m_scaleFactor); // Left
    m_handles[8]->setRect(m_handleSize / m_scaleFactor); // Rotate

    updateHandles();

}


qreal HandleFrame::scaleFactor() const
{
    return m_scaleFactor;
}


void HandleFrame::setColor(const QColor color)
{
    if (m_color != color)
    {
        m_color = color;
        m_handles[0]->setColor(m_color);
        m_handles[1]->setColor(m_color);
        m_handles[2]->setColor(m_color);
        m_handles[3]->setColor(m_color);
        m_handles[4]->setColor(m_color);
        m_handles[5]->setColor(m_color);
        m_handles[6]->setColor(m_color);
        m_handles[7]->setColor(m_color);
        m_handles[8]->setColor(m_color);
        update();
    }
}


QColor HandleFrame::color() const
{
    return m_color;
}


/*!
 * \brief Set list of items that can modifiy by handle frame
 * \param list
 */
void HandleFrame::setItems(QList<AbstractItemBase *> list)
{
    m_items = list;
    frameToSelection();
}


int HandleFrame::handleSize() const
{
    return m_handleSize;
}


void HandleFrame::setKeepAspectRatio(bool modifier)
{
    m_keepAspectRatio = modifier;
}


bool HandleFrame::isHovered()
{
    return m_isHovered;
}


/*!
 * \brief Return true or false if frame has rotation handle
 * \return
 */
bool HandleFrame::canRotate()
{
    return m_canRotate;
}

/*!
 * \brief Return true or false if frame has handles to change the height
 * \return
 */
bool HandleFrame::canHeightChange()
{
    return m_canHeightChange;
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void HandleFrame::adjustSize(qreal x, qreal y)
{
    m_oldRect = this->rect();
    m_oldPos = this->scenePos();

    qreal m_width = this->width();
    qreal m_height = this->height();

    if(m_keepAspectRatio){

        if(m_height > m_width){
            m_width =  m_width + x;
            m_height =  m_width* m_ratio;

        }else if(m_height <= m_width){
            m_height = m_height + y;
            m_width = m_height * m_ratio;
        }


    } else {
        m_width += x;
        m_height += y;
    }

    this->setRect(this->rect().x(),
                  this->rect().y(),
                  m_width,
                  m_height
                  );
}


/*!
 * \brief Calculate new size for item.
 * \param item
 */
void HandleFrame::updateItemGeometry(AbstractItemBase* item)
{
    // Calculate Size =================================================================================

    QRectF frame = item->rect();

    qreal sizeRatioX = m_oldRect.width() / frame.width();
    qreal sizeRatioY = m_oldRect.height() / frame.height();

    item->setRect( QRectF(frame.x(), frame.y(), this->rect().width() / sizeRatioX, this->rect().height() / sizeRatioY) );


    // Calculate Position =============================================================================

    qreal itemDistOldX = item->scenePos().x() - m_oldPos.x();
    qreal itemDistOldY = item->scenePos().y() - m_oldPos.y();
    qreal posRatioX = m_oldRect.width() / itemDistOldX;
    qreal posRatioY = m_oldRect.height() / itemDistOldY;
    qreal itemDistNewX = width() / posRatioX;
    qreal itemDistNewY = height() / posRatioY;

    item->setPos( this->mapToItem(item, item->pos() + QPointF(itemDistNewX, itemDistNewY)) );
}


/*!
 * \brief Update position and rect of all selected items.
 * \param x
 * \param y
 */
void HandleFrame::updateItemsSelection()
{
    foreach(AbstractItemBase* item, m_items) {
        updateItemGeometry(item);
    }

    emit sendActiveItems(m_items);
}


/*!
 * \brief Reset HandleFrame to default values.
 */
void HandleFrame::reset()
{
    this->setVisible(false);
    this->setRotation(0);
    m_items.clear();

    emit sendActiveItems(m_items);
}


/*!
 * \brief Return true if at least one artboard is fully covered in selection region. In addition m_items will contain only artboards or other items.
 * \return
 */
bool HandleFrame::selectionContainsArtboards()
{
    bool containsArtboard = false;
    m_items.clear();

    if(m_scene->selectedItems().isEmpty()) return containsArtboard;

    QList<AbstractItemBase*> artboardList = QList<AbstractItemBase*>();

    foreach(QGraphicsItem * item, m_scene->selectedItems()){
        AbstractItemBase* abItem = dynamic_cast<AbstractItemBase*>(item);

        if(abItem){
            switch(abItem->type()){
            case AbstractItemBase::Artboard:
                artboardList.append(abItem);
                containsArtboard = true;
                break;
            default:
                m_items.append(abItem);
                break;
            }
        }
    }

    // if there is at least 1 artboard override all other items
    if(containsArtboard) m_items = artboardList;

    return containsArtboard;

}


/*!
 * \brief Update handles position and visibility
 */
void HandleFrame::updateHandles()
{
    qreal offX = handleSize() / 2 / m_scaleFactor;
    qreal offY = handleSize() / 2 / m_scaleFactor;

    // set position of handles
    m_handles[0]->setPos(rect().left() - offX, rect().top() - offY); // TopLeft
    m_handles[1]->setPos(rect().center().x() - offX, rect().top() - offY); // Top
    m_handles[2]->setPos(rect().right() - offX,  rect().top() - offY); // TopRight
    m_handles[3]->setPos(rect().right() - offX,  rect().center().y() - offY); // Right
    m_handles[4]->setPos(rect().right() - offX, rect().bottom() - offY); // BottomRight
    m_handles[5]->setPos(rect().center().x() - offX, rect().bottom() - offY); // Bottom
    m_handles[6]->setPos(rect().left() - offX, rect().bottom() - offY); // BottomLeft
    m_handles[7]->setPos(rect().left() - offX, rect().center().y() - offY); // Left
    m_handles[8]->setPos(rect().center().x() - offX, rect().top() - offY - handleSize() * 3 / scaleFactor()); // Rotate

    qreal tollerance = handleSize() * 6 / scaleFactor();

    // set visibility of handles
    m_handles[0]->setVisible(m_canWidthChange && m_canHeightChange); // TopLeft
    m_handles[2]->setVisible(m_canWidthChange && m_canHeightChange); // TopRight
    m_handles[4]->setVisible(m_canWidthChange && m_canHeightChange); // BottomRight
    m_handles[6]->setVisible(m_canWidthChange && m_canHeightChange); // BottomLeft

    // hide middle handles if rect is to small
    if(this->width() < tollerance){
        m_handles[1]->setVisible(false); // Top
        m_handles[5]->setVisible(false); // Bottom
        m_handles[8]->setVisible(false); // Rotate
    }else{
        m_handles[1]->setVisible(m_canHeightChange); // Top
        m_handles[5]->setVisible(m_canHeightChange); // Bottom
        m_handles[8]->setVisible(m_canRotate); // Rotate
    }

    if(this->height() < tollerance){
        m_handles[3]->setVisible(false); // Right
        m_handles[7]->setVisible(false); // Left
    }else{
        m_handles[3]->setVisible(m_canWidthChange); // Right
        m_handles[7]->setVisible(m_canWidthChange); // Left
    }

}


void HandleFrame::rotateSelection(qreal angle)
{
    //   qDebug() << "HandleFrame::rotateSelection";

    if(!canRotate()) return;

    QPointF center = this->anchorCenter();
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(angle);
    t.translate(-center.x(), -center.y());

    foreach(AbstractItemBase* item, m_items) {

        // set position
        item->setPos(t.map(item->pos()));

        // rotate
        item->setRotation(item->rotation() + angle);
    }
}


/*!
 * \brief [SLOT] Update frame size to item selection.
 */
void HandleFrame::frameToSelection()
{

    if(m_scene->selectedItems().isEmpty()){

        reset();
        return;

        //Multiple Selection
    }else if(m_scene->selectedItems().size() >0){

        // filter Selection
        m_canRotate = !selectionContainsArtboards();

        QRectF selectionBox = selectionRect();

        if(m_items.size() == 1){
            switch(m_items.first()->frameType()){
            case AbstractItemBase::Free:
                m_canWidthChange = true;
                m_canHeightChange = true;
                break;
            case AbstractItemBase::FixedWidth:
                m_canWidthChange = false;
                m_canHeightChange = true;
                break;
            case AbstractItemBase::FixedHeight:
                m_canWidthChange = true;
                m_canHeightChange = false;
                break;
            case AbstractItemBase::FixedSize:
                m_canWidthChange = false;
                m_canHeightChange = false;
                break;
            }
        }else{
            m_canWidthChange = true;
            m_canHeightChange = true;
        }

        this->setRect(QRectF(0,0, selectionBox.width(), selectionBox.height()));
        this->setPos(selectionBox.topLeft());
        this->updateHandles();
        this->setRotation(m_items.first()->rotation());
        this->setVisible(true);

        emit sendActiveItems(m_items);
    }

}


/***************************************************
 *
 * Events
 *
 ***************************************************/

bool HandleFrame::sceneEventFilter( QGraphicsItem * watched, QEvent * event )
{
    ItemHandle *corner = dynamic_cast<ItemHandle *>(watched);
    if ( corner == nullptr ) return false;

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if ( mevent == nullptr ) return false;


    switch( event->type() )
    {
    // if the mouse went down, record the x,y coords of the press, record it inside the corner object
    case QEvent::GraphicsSceneMousePress:
        corner->setMouseState(ItemHandle::kMouseDown);
        corner->mouseDownX = mevent->pos().x();
        corner->mouseDownY = mevent->pos().y();
        m_ratio = qMax(width() / height(), height() / width());
        break;
    case QEvent::GraphicsSceneMouseRelease:
        corner->setMouseState(ItemHandle::kMouseReleased);
        break;
    case QEvent::GraphicsSceneMouseMove:
        corner->setMouseState(ItemHandle::kMouseMoving );
        break;
    default:
        // we dont care about the rest of the events
        return false;
        break;
    }


    if ( corner->getMouseState() == ItemHandle::kMouseMoving )
    {
        qreal x = mevent->pos().x(), y = mevent->pos().y();

        // depending on which corner has been grabbed, we want to move the position
        // of the item as it grows/shrinks accordingly. so we need to eitehr add
        // or subtract the offsets based on which corner this is.
        int XaxisSign = 0;
        int YaxisSign = 0;

        switch( corner->getCorner() )
        {
        case ItemHandle::TopLeft:
            XaxisSign = 1;
            YaxisSign = 1;
            break;
        case ItemHandle::Top:
            XaxisSign = 0;
            YaxisSign = 1;
            break;
        case ItemHandle::TopRight:
            XaxisSign = -1;
            YaxisSign = 1;
            break;
        case ItemHandle::Right:
            XaxisSign = -1;
            YaxisSign = 0;
            break;
        case ItemHandle::BottomRight:
            XaxisSign = -1;
            YaxisSign = -1;
            break;
        case ItemHandle::Bottom:
            XaxisSign = 0;
            YaxisSign = -1;
            break;
        case ItemHandle::BottomLeft:
            XaxisSign = 1;
            YaxisSign = -1;
            break;
        case ItemHandle::Left:
            XaxisSign = 1;
            YaxisSign = 0;
            break;
        }

        // if the mouse is being dragged, calculate a new size and also re-position
        // the box to give the appearance of dragging the corner out/in to resize the box

        qreal xMoved = corner->mouseDownX - x;
        qreal yMoved = corner->mouseDownY - y;

        qreal newWidth = this->rect().width() + ( XaxisSign * xMoved);
        if ( newWidth < 1 ) newWidth  = 1;

        qreal newHeight = this->rect().height() + (YaxisSign * yMoved) ;
        if ( newHeight < 1 ) newHeight = 1;

        qreal deltaW  =   newWidth - this->rect().width() ;
        qreal deltaH =   newHeight - this->rect().height() ;

        // adjust frame size
        this->adjustSize(  deltaW ,   deltaH);

        qreal deltaWidth = deltaW * (-1);
        qreal deltaHeight = deltaH * (-1);

        qreal newX;
        qreal newY;

        switch( corner->getCorner() ){
        case ItemHandle::TopLeft:{
            if(m_keepAspectRatio){
                if(height() > width()){
                    newX = anchorBottomRight().x() - width() + deltaWidth;
                    newY = anchorBottomRight().y() - height() + deltaWidth * m_ratio;

                }else {
                    newX = anchorBottomRight().x() - width() + deltaHeight * m_ratio;
                    newY = anchorBottomRight().y() - height() + deltaHeight;
                }
            }else{
                newX = anchorBottomRight().x() - width() + deltaWidth;
                newY = anchorBottomRight().y() - height() + deltaHeight;
            }
            this->setPos(newX,newY);


            break;
        }
        case ItemHandle::Top:
        case ItemHandle::TopRight:{
            if(m_keepAspectRatio){

                if(height() > width()){
                    newY = anchorBottomRight().y() - height() + deltaWidth * m_ratio;

                }else {
                    newY = anchorBottomRight().y() - height() + deltaHeight;
                }


            }else{
                newY = anchorBottomRight().y() - height() + deltaHeight;
            }
            this->setPos(this->pos().x(),newY);

            break;
        }
        case ItemHandle::Left:
        case ItemHandle::BottomLeft:{
            if(m_keepAspectRatio){
                if(height() > width()){
                    newX = anchorBottomRight().x() - width() + deltaWidth;
                }else {
                    newX = anchorBottomRight().x() - width() + deltaHeight * m_ratio;
                }
            }else{
                newX = anchorBottomRight().x() - width() + deltaWidth;
            }
            this->setPos(newX, this->pos().y());

            break;
        }
        case ItemHandle::Right:
        case ItemHandle::Bottom:
        case ItemHandle::BottomRight:
        default:
            // only size is changing
            break;
        }


        // Set corner positions
        updateHandles();

        // Update selected item sizes and positions
        updateItemsSelection();

        this->update();

    }

    return true;// true => do not send event to watched - we are finished with this event
}



void HandleFrame::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);

}

//void HandleFrame::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//	Q_UNUSED(event);
//	m_isHovered = true;
//	qDebug() << "HandleFrame::HoverEnter";
//}

//void HandleFrame::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//	Q_UNUSED(event);
//	m_isHovered = false;
//	qDebug() << "HandleFrame::HoverLeave";
//}


void HandleFrame::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);
    m_dragStart = event->pos();
}


void HandleFrame::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    QPointF newPos = event->pos() ;
    QPointF m_loc = (newPos - m_dragStart);
    this->moveBy(m_loc.x(), m_loc.y());
}


void HandleFrame::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    painter->save();

    QPen pen = this->pen();
    pen.setCosmetic(true);

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

//    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    // fix the line on half pixels
    if (scaleFactor() > 2 ) {
        painter->drawRect(rect());
    }else{
        painter->drawRect(adjustedRect());
    }

    if(m_handles[8]->isVisible()){
        painter->drawLine(QPointF(rect().center().x(), rect().top() - m_rotationHandleDistance / scaleFactor()),
                          QPointF(rect().center().x(), rect().top()));

    }

    painter->restore();

}

