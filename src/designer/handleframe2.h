/*
 * Based on Code of David W. Drell
 * Copyright 2010, David W. Drell
 * http://www.davidwdrell.net/wordpress/?page_id=36
 *
 * This is free sample code. Use as you wish, no warranties.
 */

#ifndef ITEMHANDLE2_H
#define ITEMHANDLE2_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QGraphicsDropShadowEffect>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItemGroup>

#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/item/itemgroup.h"
#include "src/item/artboard.h"


class CanvasScene;

class ItemHandle2 : public QGraphicsItem
{

public:

	enum {
		kMouseReleased=0,
		kMouseDown,
		kMouseMoving
	}; ///< define the mouse states

	enum Handle{
		TopLeft = 0,
		Top = 1,
		TopRight = 2,
		Right = 3,
		BottomRight = 4,
		Bottom = 5,
		BottomLeft = 6,
		Left = 7,
	};

    explicit ItemHandle2(QGraphicsItem *parent = 0,  Handle corner = Handle::TopLeft, int buffer = 3);

	Handle getCorner(); ///< allows the owner to find out which coner this is
	void setMouseState(int); ///< allows the owner to record the current mouse state
	int  getMouseState(); ///< allows the owner to get the current mouse state
	virtual QRectF rect() const;
	virtual void setRect(qreal width);


	qreal mouseDownX;
	qreal mouseDownY;

private:

	virtual QRectF boundingRect() const;
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
	virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

	QColor  m_color;
	QPen    m_Pen;
	qreal   m_width;
	qreal   m_height;
	Handle  m_corner;
	int     m_mouseButtonState;
	int     m_buffer;

};


/*****************************************************************************************/


class HandleFrame2 : public QObject, public QGraphicsItem
{

	Q_OBJECT

public:
    HandleFrame2(CanvasScene *scene, int buffer = 3, qreal grid = 1);

	// Properties
	virtual QRectF boundingRect() const;
	virtual QRectF adjustedRect() const;
	QRectF selectionBoundingRect(qreal &angle);
	virtual void moveBy(qreal dx, qreal dy);

	void setRect(QRectF rect);
	void setRect(qreal x, qreal y, qreal width, qreal height);
	QRectF rect() const;
	qreal width() const;
	qreal height() const;
	QPointF anchorTopLeft() const;
	QPointF anchorTop() const;
	QPointF anchorTopRight() const;
	QPointF anchorRight() const;
	QPointF anchorBottomRight() const;
	QPointF anchorBottom() const;
	QPointF anchorBottomLeft() const;
	QPointF anchorLeft() const;
	QPointF anchorCenter() const;
	void setPen(QPen pen);
	QPen pen() const;
	void setScaleFactor(qreal factor);
	qreal scaleFactor() const;
	int buffer() const;
	void setGridSpace(int space);
	void setShiftModifier(bool modifier);
	bool isHovered();

	// Members
	void updateHandleFrame();
	void setup();
//	void group();
//	void unGroup();

	void rotateSelection(qreal angle);



private:

	CanvasScene *	m_scene;
	QPointF     m_dragStart;
	int         m_gridSpace;
	QPointF     m_cornerDragStart;
	QRectF		m_oldRect;
	QPointF		m_oldPos;
    ItemHandle2* m_handles[8];
	int         m_buffer;
	bool		m_shiftModifier;
	QPen        m_pen;
	qreal       m_scaleFactor;
	QRectF		m_rect;
	qreal		m_ratio;
	bool		m_isTextOnly;
//	QGraphicsItemGroup *m_selectionGroup;
	bool		m_isHovered;

	void adjustSize(int x, int y);
	QPointF updateItemsPosition(QGraphicsItem *item);
	QRectF updateItemSize(QRectF frame);
	void updateItemsSelection(int x, int y);
	void reset();

	void sendActiveItems();

	// Events
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event

	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );///< allows the main object to be moved in the scene by capturing the mouse move events
	virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
	virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
//	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;

public slots:
	void slotFrameToSelection();

signals:
	void emitActiveItem(ItemBase * item);

};


#endif // ITEMHANDLE2_H
