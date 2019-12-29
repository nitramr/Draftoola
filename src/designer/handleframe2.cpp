#include "handleframe2.h"

#include <QDebug>
#include <QtMath>

#include "canvasscene.h"

ItemHandle2::ItemHandle2(QGraphicsItem *parent,  Handle corner, int buffer) :
	QGraphicsItem(parent),
	mouseDownX(0),
	mouseDownY(0),
	m_Pen(),
	m_corner(corner),
	m_mouseButtonState(kMouseReleased)
{
	setParentItem(parent);

	m_buffer = buffer;
	m_width = 2 * m_buffer;
	m_height = 2 * m_buffer;
	m_color = QColor(0, 128, 255);

	m_Pen.setCosmetic(true);
	m_Pen.setColor(m_color);

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

void ItemHandle2::setMouseState(int s)
{
	m_mouseButtonState = s;
}

int ItemHandle2::getMouseState()
{
	return m_mouseButtonState;
}

QRectF ItemHandle2::rect() const
{
	return QRectF(0, 0, m_width, m_height);
}

void ItemHandle2::setRect(qreal width)
{
	m_width = width;
	m_height = width;
}

QRectF ItemHandle2::boundingRect() const
{
	return rect();
}

ItemHandle2::Handle ItemHandle2::getCorner()
{
	return m_corner;
}

/***************************************************
 *
 * Events
 *
 ***************************************************/

// we have to implement the mouse events to keep the linker happy,
// but just set accepted to false since are not actually handling them

void ItemHandle2::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
	event->setAccepted(false);
}

void ItemHandle2::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
	event->setAccepted(false);
}

void ItemHandle2::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	event->setAccepted(true);
}

void ItemHandle2::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
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
	default:
		break;
	}
}

void ItemHandle2::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	event->setAccepted(false);
}

void ItemHandle2::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	event->setAccepted(false);
}


void ItemHandle2::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	painter->save();
	painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
	painter->setPen(m_Pen);
	painter->setBrush(QBrush(Qt::white));
	painter->drawRect(this->rect());
	painter->restore();

}

/*******************************************************************************************************************************/

/*******************************
 *
 * Handle Frame
 *
 *******************************/

HandleFrame2::HandleFrame2(CanvasScene *scene, int buffer, qreal grid): QObject(), QGraphicsItem(),
	m_scene(scene),
	m_dragStart(0,0),
	m_gridSpace(grid),
	m_cornerDragStart(0,0),
	m_buffer(buffer),
	m_shiftModifier(false),
	m_pen(QPen()),
	m_scaleFactor(1.0),
	m_rect(QRectF(0,0,10,10)),
	m_ratio(1.0),
	m_isTextOnly(false)
{

    m_handles[0] = new ItemHandle2(this,ItemHandle2::TopLeft, m_buffer);
    m_handles[1] = new ItemHandle2(this,ItemHandle2::Top, m_buffer);
    m_handles[2] = new ItemHandle2(this,ItemHandle2::TopRight, m_buffer);
    m_handles[3] = new ItemHandle2(this,ItemHandle2::Right, m_buffer);
    m_handles[4] = new ItemHandle2(this,ItemHandle2::BottomRight, m_buffer);
    m_handles[5] = new ItemHandle2(this,ItemHandle2::Bottom, m_buffer);
    m_handles[6] = new ItemHandle2(this,ItemHandle2::BottomLeft, m_buffer);
    m_handles[7] = new ItemHandle2(this,ItemHandle2::Left, m_buffer);

	m_isHovered = false;

	this->setPen(QPen(QColor(0, 128, 255)));
	this->setVisible(false);
	this->setAcceptHoverEvents(true);
	this->setFlags(QGraphicsItem::ItemDoesntPropagateOpacityToChildren);
	this->setZValue(99999999);

	connect(m_scene, SIGNAL(selectionChanged()), this,SLOT(slotFrameToSelection()));

}


/***************************************************
 *
 * Properties
 *
 ***************************************************/



QRectF HandleFrame2::boundingRect() const
{
	return QRectF(rect().x() - 2*buffer(), rect().y() - 2*buffer(), rect().width() + buffer() * 4, rect().height() + buffer() * 4);
}

QRectF HandleFrame2::adjustedRect() const
{
	return QRectF(rect().x() + 0.5, rect().y() + 0.5, rect().width() - 1, rect().height() - 1);
}

QRectF HandleFrame2::selectionBoundingRect(qreal &angle)
{

	qDebug() << "Enter";

	//	deselect();

	QRectF selectionBoundingRect;

	QList<QGraphicsItem *> selectedItems = m_scene->selectedItems();
	foreach(QGraphicsItem *current, selectedItems) {

		ItemRect * warect = dynamic_cast<ItemRect*>(current);
		ItemOval * waoval = dynamic_cast<ItemOval*>(current);
		ItemText * watext = dynamic_cast<ItemText*>(current);
//		WAGroup * wagroup = dynamic_cast<WAGroup*>(current);
		Artboard * artboard = dynamic_cast<Artboard*>(current);

		if(artboard){
			selectionBoundingRect = QRectF(artboard->scenePos().x(), artboard->scenePos().y(), artboard->rect().width(), artboard->rect().height());
			m_isTextOnly = false;
		}
        if(watext){
            selectionBoundingRect = selectionBoundingRect.united(QRectF(watext->scenePos().x(), watext->scenePos().y(), watext->rect().width(), watext->rect().height()));
            m_isTextOnly = true;
        }
		if(warect){
			selectionBoundingRect = selectionBoundingRect.united(QRectF(warect->scenePos().x(), warect->scenePos().y(), warect->rect().width(), warect->rect().height()));
			m_isTextOnly = false;
		}
		if(waoval){
			selectionBoundingRect = selectionBoundingRect.united(QRectF(waoval->scenePos().x(), waoval->scenePos().y(), waoval->rect().width(), waoval->rect().height()));
			m_isTextOnly = false;
		}
//		if(wagroup){
//			selectionBoundingRect = selectionBoundingRect.united(QRectF(wagroup->scenePos().x(), wagroup->scenePos().y(), wagroup->rect().width(), wagroup->rect().height()));
//			m_isTextOnly = false;
//		}

		angle = current->rotation();

	}

	if(selectedItems.count() != 1) angle = 0;

	return selectionBoundingRect;
}

void HandleFrame2::moveBy(qreal dx, qreal dy)
{

//	if(!m_selectionGroup) return;

	dx = (static_cast<int>(dx) / m_gridSpace) * m_gridSpace;
	dy = (static_cast<int>(dy) / m_gridSpace) * m_gridSpace;

	QGraphicsItem::moveBy(dx,dy);

		QList<QGraphicsItem *> selectedItems = m_scene->selectedItems();
		foreach(QGraphicsItem *current, selectedItems) {

			QGraphicsItem * item = current;//dynamic_cast<ItemBase*>(current);

			if(!item) continue;

			item->moveBy(dx,dy);

		}

//	m_selectionGroup->moveBy(dx,dy);

	sendActiveItems();

}

void HandleFrame2::setRect(QRectF rect)
{
	m_rect = rect;
}

void HandleFrame2::setRect(qreal x, qreal y, qreal width, qreal height)
{
	setRect(QRectF(x,y,width, height));
}

QRectF HandleFrame2::rect() const
{
	return m_rect;
}

qreal HandleFrame2::width() const
{
	return this->rect().width();
}

qreal HandleFrame2::height() const
{
	return this->rect().height();
}

QPointF HandleFrame2::anchorTopLeft() const
{
	return this->scenePos();
}

QPointF HandleFrame2::anchorTop() const
{
	return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y());
}

QPointF HandleFrame2::anchorTopRight() const
{
	return QPointF(this->scenePos().x() + width(), this->scenePos().y());
}

QPointF HandleFrame2::anchorRight() const
{
	return QPointF(this->scenePos().x() + width(), this->scenePos().y() + height() / 2);
}

QPointF HandleFrame2::anchorBottomRight() const
{
	return QPointF(this->scenePos().x() + width(), this->scenePos().y() + height());
}

QPointF HandleFrame2::anchorBottom() const
{
	return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y() + height());
}

QPointF HandleFrame2::anchorBottomLeft() const
{
	return QPointF(this->scenePos().x(), this->scenePos().y() + height());
}

QPointF HandleFrame2::anchorLeft() const
{
	return QPointF(this->scenePos().x(), this->scenePos().y() + height() / 2);
}

QPointF HandleFrame2::anchorCenter() const
{
	return QPointF(this->scenePos().x() + width() / 2, this->scenePos().y() + height() / 2);
}

void HandleFrame2::setPen(QPen pen)
{
	m_pen = pen;
}

QPen HandleFrame2::pen() const{
	return m_pen;
}

void HandleFrame2::setScaleFactor(qreal factor)
{
	m_scaleFactor = factor;

	m_handles[0]->setRect(m_buffer * 2 / m_scaleFactor); // TopLeft
	m_handles[1]->setRect(m_buffer * 2 / m_scaleFactor); // Top
	m_handles[2]->setRect(m_buffer * 2 / m_scaleFactor); // TopRight
	m_handles[3]->setRect(m_buffer * 2 / m_scaleFactor); // Right
	m_handles[4]->setRect(m_buffer * 2 / m_scaleFactor); // BottomRight
	m_handles[5]->setRect(m_buffer * 2 / m_scaleFactor); // Bottom
	m_handles[6]->setRect(m_buffer * 2 / m_scaleFactor); // BottomLeft
	m_handles[7]->setRect(m_buffer * 2 / m_scaleFactor); // Left

	updateHandleFrame();

}

qreal HandleFrame2::scaleFactor() const
{
	return m_scaleFactor;
}

int HandleFrame2::buffer() const
{
	return m_buffer;
}


void HandleFrame2::setShiftModifier(bool modifier)
{
	m_shiftModifier = modifier;
}

bool HandleFrame2::isHovered()
{
	return m_isHovered;
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void HandleFrame2::adjustSize(int x, int y)
{
	m_oldRect = this->rect();
	m_oldPos = this->scenePos();

	qreal m_width = this->width();
	qreal m_height = this->height();

	if(m_shiftModifier){

		if(m_height > m_width){
			m_width = m_width + x;
			m_height = m_width* m_ratio;

		}else if(m_height <= m_width){
			m_height = m_height + y;
			m_width = m_height * m_ratio;
		}


	} else {
		round(m_width += x);
		round(m_height += y);
	}

	this->setRect(this->rect().x(),
				  this->rect().y(),
				  m_width,
				  m_height
				  );
}

QPointF HandleFrame2::updateItemsPosition(QGraphicsItem *item)
{

//	QPointF posItem(item->pos());
//	QPointF relItem = this->mapFromItem(item, QPointF());

//	qDebug() << "relItem Pos:" << relItem;

//	return posItem;


	QPointF posHandle = m_oldPos;
	QPointF posItem = item->pos();
	qreal diffAX = posItem.x() - posHandle.x();
	qreal diffAY = posItem.y() - posHandle.y();
	qreal diffZX = m_oldRect.width() - diffAX;
	qreal diffZY = m_oldRect.height() - diffAY;

	qreal diffRatioX = qMax(diffAX / diffZX, diffZX / diffAX);
	qreal diffRatioY = qMax(diffAY / diffZY, diffZY / diffAY);

	qreal diffAXnew = posItem.x() - this->pos().x();
	qreal diffAYnew = posItem.y() - this->pos().y();

	qreal ratioX = this->pos().x() + (diffAXnew / diffRatioX);
	qreal ratioY = this->pos().y() + (diffAYnew / diffRatioY);

	qDebug() << "*************************************";
	qDebug() << "posHandle" << posHandle;
	qDebug() << "posItem" << posItem;
	qDebug() << "diffAX" << diffAX<< "diffAY" << diffAY;
	qDebug() << "diffZX" << diffZX<< "diffZY" << diffZY;
	qDebug() << "diffRatioX" << diffRatioX<< "diffRatioY" << diffRatioY;
	qDebug() << "ratioX" << ratioX << "ratioY" << ratioY;

	return QPointF(ratioX, ratioY);

}

QRectF HandleFrame2::updateItemSize(QRectF frame)
{
	qreal ratioWidth = m_oldRect.width() / frame.width();
	qreal ratioHeight = m_oldRect.height() / frame.height();

	return QRectF(frame.x(),frame.y(), this->rect().width() / ratioWidth, this->rect().height() / ratioHeight);
//	newRect.translate(rect().topLeft() - newRect.topLeft());
//	return newRect;
}

void HandleFrame2::updateItemsSelection(int x, int y)
{

//	  QPointF center = this->rect().center();
//	  QTransform t;
//	  t.translate(center.x(), center.y());
//	  t.rotate(angle);
//	  t.translate(-center.x(), -center.y());
	  foreach(QGraphicsItem* item, m_scene->selectedItems()) {

		// Scale
		Artboard * itemArtboard = dynamic_cast<Artboard*>(item);
		if(itemArtboard){
			itemArtboard->setRect(updateItemSize(itemArtboard->rect()));
			itemArtboard->setPos(updateItemsPosition(itemArtboard));
		}

		ItemText * itemText = dynamic_cast<ItemText*>(item);
		if(itemText){
			itemText->setRect(updateItemSize(itemText->rect()));
            itemText->setPos(updateItemsPosition(itemText));

		}

		ItemRect * itemRect = dynamic_cast<ItemRect*>(item);
		if(itemRect){
			itemRect->setRect(updateItemSize(itemRect->rect()));
//			itemRect->moveBy(x,y);
			itemRect->setPos(updateItemsPosition(itemRect));

		}

		ItemOval * itemOval = dynamic_cast<ItemOval*>(item);
		if(itemOval){
			itemOval->setRect(updateItemSize(itemOval->rect()));
//			itemOval->moveBy(x,y);
			itemOval->setPos(updateItemsPosition(itemOval));

		}

		// set position
//		item->setPos(t.map(item->pos()));

	}

	sendActiveItems();
}

void HandleFrame2::reset()
{
	this->setVisible(false);
	this->setRotation(0);
    emit emitActiveItem(nullptr);
}


void HandleFrame2::sendActiveItems()
{
	if(m_scene->selectedItems().size() == 1){
		ItemBase* m_itemBase = dynamic_cast<ItemBase*>(m_scene->selectedItems()[0]);
		if(m_itemBase){
			emit emitActiveItem(m_itemBase);
        }else emit emitActiveItem(nullptr);

    }else emit emitActiveItem(nullptr);
}


void HandleFrame2::updateHandleFrame()
{
	qreal posX = rect().x() - buffer() / m_scaleFactor;
	qreal posY = rect().y() - buffer() / m_scaleFactor;
	qreal width = rect().width() + 2 * buffer();
	qreal height = rect().height() + 2 * buffer();

	m_handles[0]->setPos(posX, posY); // TopLeft
	m_handles[1]->setPos(posX + width / 2 - buffer(), posY); // Top
	m_handles[2]->setPos(posX + width - 2 * buffer(),  posY); // TopRight
	m_handles[3]->setPos(posX + width - 2 * buffer(),  posY + height / 2 - buffer()); // Right
	m_handles[4]->setPos(posX + width - 2 * buffer(), posY + height - 2 * buffer()); // BottomRight
	m_handles[5]->setPos(posX + width / 2 - buffer(), posY + height - 2 * buffer()); // Bottom
	m_handles[6]->setPos(posX, posY + height - 2 * buffer()); // BottomLeft
	m_handles[7]->setPos(posX, posY + height / 2 - buffer()); // Left

	qreal tollerance = m_buffer * 6 / m_scaleFactor;

	// is Textfield
	if(m_isTextOnly){
		m_handles[0]->setVisible(false); // TopLeft
		m_handles[1]->setVisible(false); // Top
		m_handles[2]->setVisible(false); // TopRight
		m_handles[3]->setVisible(true);  // Right
		m_handles[4]->setVisible(false); // BottomRight
		m_handles[5]->setVisible(false); // Bottom
		m_handles[6]->setVisible(false); // BottomLeft
		m_handles[7]->setVisible(true);  // Left
	}else{
		m_handles[0]->setVisible(true); // TopLeft
		m_handles[1]->setVisible(true); // Top
		m_handles[2]->setVisible(true); // TopRight
		m_handles[3]->setVisible(true);  // Right
		m_handles[4]->setVisible(true); // BottomRight
		m_handles[5]->setVisible(true); // Bottom
		m_handles[6]->setVisible(true); // BottomLeft
		m_handles[7]->setVisible(true);  // Left

		// hide middle handles if rect is to small
		if(this->width() < tollerance){
			m_handles[1]->setVisible(false);
			m_handles[5]->setVisible(false);
		}else if(this->width() > tollerance){
			m_handles[1]->setVisible(true);
			m_handles[5]->setVisible(true);
		}

		if(this->height() < tollerance){
			m_handles[3]->setVisible(false);
			m_handles[7]->setVisible(false);
		}else if(this->height() > tollerance){
			m_handles[3]->setVisible(true);
			m_handles[7]->setVisible(true);
		}

	}
}

void HandleFrame2::setup()
{
	m_handles[0]->installSceneEventFilter(this);
	m_handles[1]->installSceneEventFilter(this);
	m_handles[2]->installSceneEventFilter(this);
	m_handles[3]->installSceneEventFilter(this);
	m_handles[4]->installSceneEventFilter(this);
	m_handles[5]->installSceneEventFilter(this);
	m_handles[6]->installSceneEventFilter(this);
	m_handles[7]->installSceneEventFilter(this);


}

//void HandleFrame::group()
//{
//	qDebug() << "HandleFrame::Group";

//	QList<QGraphicsItem *> selectedItems = m_scene->selectedItems();

//	if(selectedItems.size() >0){
//		m_selectionGroup = m_scene->createItemGroup(selectedItems);//new QGraphicsItemGroup();
//		qDebug() << "Group" << m_selectionGroup;
//		this->setVisible(true);
//	}
//}

//void HandleFrame::unGroup()
//{
//	qDebug() << "HandleFrame::unGroup";
//	if(m_selectionGroup){
//		qDebug() << "SelectionGroup is valid";
//		if(m_scene->items().contains(m_selectionGroup)){
//			m_scene->destroyItemGroup(m_selectionGroup);
//			reset();
//			qDebug() << "UnGroup";
//		}


//	}


//}

void HandleFrame2::rotateSelection(qreal angle)
{
	qDebug() << "HandleFrame::rotateSelection";

	  QPointF center = this->rect().center();
	  QTransform t;
	  t.translate(center.x(), center.y());
	  t.rotate(angle);
	  t.translate(-center.x(), -center.y());

	  foreach(QGraphicsItem* item, m_scene->selectedItems()) {

		// set position
		item->setPos(t.map(item->pos()));

		// rotate
		item->setRotation(item->rotation() + angle);
	}
}


void HandleFrame2::slotFrameToSelection()
{

	if(m_scene->selectedItems().size() == 0){

		reset();

		return;

		//Multiple Selection
	}else if(m_scene->selectedItems().size() >0){

		qDebug() << "Selected Items" << m_scene->selectedItems().size();

		qreal angle;
		QRectF selectionBox = selectionBoundingRect(angle);

		this->setRect(QRectF(0,0, selectionBox.width(), selectionBox.height()));
		this->setPos(selectionBox.topLeft());
		this->updateHandleFrame();
		this->setRotation(angle);
		this->setVisible(true);

		sendActiveItems();

		//        ItemBase* m_itemBase = dynamic_cast<ItemBase*>(selecitems[0]);
		//        ArtboardLabel* m_artboardLabel = dynamic_cast<ArtboardLabel*>(selecitems[0]);
		//        if(m_itemBase){


		//            m_handleFrame->setHost(m_itemBase);
		//			m_handleFrame->setVisible(true);

		//            emit emitActiveItem(m_itemBase);

		//        } else if(m_artboardLabel){

		//            Artboard * m_artboard = dynamic_cast<Artboard*>(m_artboardLabel->parentItem());
		//            if(!m_artboard) return;


		//            m_handleFrame->setHost(m_artboard);
		//			m_handleFrame->setVisible(true);


		//            emit emitActiveItem(m_artboard);

		//        }else {
		//            m_handleFrame->setVisible(false);
		//            m_handleFrame->setHost(new ItemBase());
		//            emit emitActiveItem(0);
		//            return;
		//        }
	}

}

/***************************************************
 *
 * Events
 *
 ***************************************************/

bool HandleFrame2::sceneEventFilter( QGraphicsItem * watched, QEvent * event )
{
    ItemHandle2 *corner = dynamic_cast<ItemHandle2 *>(watched);
    if ( corner == nullptr ) return false;

	QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if ( mevent == nullptr ) return false;


	switch( event->type() )
	{
	// if the mouse went down, record the x,y coords of the press, record it inside the corner object
	case QEvent::GraphicsSceneMousePress:
        corner->setMouseState(ItemHandle2::kMouseDown);
		corner->mouseDownX = mevent->pos().x();
		corner->mouseDownY = mevent->pos().y();
		m_ratio = qMax(width() / height(), height() / width());
		break;
	case QEvent::GraphicsSceneMouseRelease:
        corner->setMouseState(ItemHandle2::kMouseReleased);
		break;
	case QEvent::GraphicsSceneMouseMove:
        corner->setMouseState(ItemHandle2::kMouseMoving );
		break;
	default:
		// we dont care about the rest of the events
		return false;
		break;
	}


    if ( corner->getMouseState() == ItemHandle2::kMouseMoving )
	{
		qreal x = mevent->pos().x(), y = mevent->pos().y();

		// depending on which corner has been grabbed, we want to move the position
		// of the item as it grows/shrinks accordingly. so we need to eitehr add
		// or subtract the offsets based on which corner this is.
		int XaxisSign = 0;
		int YaxisSign = 0;

		switch( corner->getCorner() )
		{
        case ItemHandle2::TopLeft:
			XaxisSign = 1;
			YaxisSign = 1;
			break;
        case ItemHandle2::Top:
			XaxisSign = 0;
			YaxisSign = 1;
			break;
        case ItemHandle2::TopRight:
			XaxisSign = -1;
			YaxisSign = 1;
			break;
        case ItemHandle2::Right:
			XaxisSign = -1;
			YaxisSign = 0;
			break;
        case ItemHandle2::BottomRight:
			XaxisSign = -1;
			YaxisSign = -1;
			break;
        case ItemHandle2::Bottom:
			XaxisSign = 0;
			YaxisSign = -1;
			break;
        case ItemHandle2::BottomLeft:
			XaxisSign = 1;
			YaxisSign = -1;
			break;
        case ItemHandle2::Left:
			XaxisSign = 1;
			YaxisSign = 0;
			break;
		}

		// if the mouse is being dragged, calculate a new size and also re-position
		// the box to give the appearance of dragging the corner out/in to resize the box




		int xMoved = corner->mouseDownX - x;
		int yMoved = corner->mouseDownY - y;

		int newWidth = this->rect().width() + ( XaxisSign * xMoved);
		if ( newWidth < 1 ) newWidth  = 1;

		int newHeight = this->rect().height() + (YaxisSign * yMoved) ;
		if ( newHeight < 1 ) newHeight = 1;

		int deltaW  =   newWidth - this->rect().width() ;
		int deltaH =   newHeight - this->rect().height() ;


		qDebug() << "deltaW:" << deltaW << "deltaH:" << deltaH;

		adjustSize(  deltaW ,   deltaH);

		qreal deltaWidth = deltaW * (-1);
		qreal deltaHeight = deltaH * (-1);

		qDebug() << "deltaWidth:" << deltaWidth << "deltaHeight:" << deltaHeight;

		qreal newX;
		qreal newY;

		switch( corner->getCorner() ){
        case ItemHandle2::TopLeft:{
			if(m_shiftModifier){
				if(height() > width()){
					newX = anchorBottomRight().x() - width() + deltaWidth;
					newY = anchorBottomRight().y() - height() + deltaWidth * m_ratio;

				}else if(height() <= width()){
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
        case ItemHandle2::Top:
        case ItemHandle2::TopRight:{
			if(m_shiftModifier){

				if(height() > width()){
					newY = anchorBottomRight().y() - height() + deltaWidth * m_ratio;

				}else if(height() <= width()){
					newY = anchorBottomRight().y() - height() + deltaHeight;
				}


			}else{
				newY = anchorBottomRight().y() - height() + deltaHeight;
			}
			this->setPos(this->pos().x(),newY);
			break;
		}
        case ItemHandle2::Left:
        case ItemHandle2::BottomLeft:{
			if(m_shiftModifier){
				if(height() > width()){
					newX = anchorBottomRight().x() - width() + deltaWidth;
				}else if(height() <= width()){
					newX = anchorBottomRight().x() - width() + deltaHeight * m_ratio;
				}
			}else{
				newX = anchorBottomRight().x() - width() + deltaWidth;
			}
			this->setPos(newX, this->pos().y());

			break;
		}
        case ItemHandle2::Right:
        case ItemHandle2::Bottom:
        case ItemHandle2::BottomRight:
		default:
			// only size is changing
			break;
		}


		// Set corner positions
		updateHandleFrame();

		// Update selected item sizes and positions
		updateItemsSelection(deltaW, deltaH);

		this->update();

	}

	return true;// true => do not send event to watched - we are finished with this event
}



void HandleFrame2::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
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


void HandleFrame2::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	event->setAccepted(true);
	m_dragStart = event->pos();

}


void HandleFrame2::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{

	QPointF newPos = event->pos() ;
	QPointF m_loc = (newPos - m_dragStart);
	this->moveBy(m_loc.x(), m_loc.y());

}


void HandleFrame2::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

	painter->save();
	painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

	QPen pen = this->pen();
	pen.setCosmetic(true);

	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);

	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
	if (lod > 2 ) {
		painter->drawRect(rect());
	}else{
		painter->drawRect(adjustedRect());
	}

	painter->restore();

}

