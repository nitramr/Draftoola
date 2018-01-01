/*
 * Based on Code of David W. Drell
 * Copyright 2010, David W. Drell
 * http://www.davidwdrell.net/wordpress/?page_id=36
 *
 * This is free sample code. Use as you wish, no warranties.
 */

#ifndef ITEMHANDLE_H
#define ITEMHANDLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QGraphicsDropShadowEffect>

#include "whiteprint/item/itembase.h"


class ItemHandle : public QGraphicsItem
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

    explicit ItemHandle(QGraphicsItem *parent = 0,  Handle corner = Handle::TopLeft, int buffer = 3);

    Handle getCorner(); ///< allows the owner to find out which coner this is
    void setMouseState(int); ///< allows the owner to record the current mouse state
    int  getMouseState(); ///< allows the owner to get the current mouse state
	virtual QRectF rect() const;
	virtual QRectF rectAdjusted() const;


    qreal mouseDownX;
    qreal mouseDownY;

private:

	virtual QRectF boundingRect() const;
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
	virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

    // once the hover event handlers are implemented in this class,
    // the mouse events must allow be implemented because of
    // some linkage issue - apparrently there is some connection
    // between the hover events and mouseMove/Press/Release
    // events which triggers a vtable issue
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

    QColor  m_color;
    QPen    m_Pen;
    qreal   m_width;
    qreal   m_height;
    Handle  m_corner;
    int     m_mouseButtonState;
    int     m_buffer;

};

class HandleFrame : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

public:
    HandleFrame(int buffer = 3, qreal grid = 1, QObject * parent = 0);

    // Properties
	virtual QRectF boundingRect() const;
	virtual QRectF rectAdjusted() const;
    virtual void moveBy(qreal dx, qreal dy);

    void setPen(QPen pen);
    QPen pen() const;
    void setScaleFactor(qreal factor);
    qreal scaleFactor() const;
    int buffer() const;
    void setGridSpace(int space);
    void setHost(ItemBase *host);
    void setCornerPositions();
    void installFilter();
    void setIsResize(bool resizeOnly);
    bool isResize();
    void setShiftModifier(bool modifier);

private:

    QPointF     m_dragStart;
    int         m_gridSpace;
    QPointF     m_cornerDragStart;
    ItemBase *  m_host;
    ItemHandle* m_corners[8];
    int         m_buffer;
    int         m_bufferBak;
    bool        m_resizeOnly;
	QRectF		m_rect;
	bool		m_shiftModifier;
    QPen        m_pen;
    qreal       m_scaleFactor;
    bool        m_isZoom;

	void adjustSize(int x, int y);
	void mapToHost();

    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events

    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );///< allows the main object to be moved in the scene by capturing the mouse move events
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

//    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;

signals:
    void emitItemChange();

};


#endif // ITEMHANDLE_H
