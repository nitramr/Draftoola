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
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItemGroup>

#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <itemgroup.h>
#include <artboard.h>


class CanvasScene;

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
        Rotate = 8
    };

    enum Style{
        Square = 0,
        Round = 1
    };

    explicit ItemHandle(QGraphicsItem *parent = nullptr,  Handle corner = Handle::TopLeft, int handleSize = 6, QColor color = QColor(0, 128, 255), Style style = Style::Square);

    Handle getCorner(); ///< allows the owner to find out which coner this is
    void setMouseState(int); ///< allows the owner to record the current mouse state
    int  getMouseState(); ///< allows the owner to get the current mouse state

    virtual QRectF rect() const;
    virtual void setRect(qreal width);

    void setColor(const QColor color);
    QColor color() const;


    qreal mouseDownX;
    qreal mouseDownY;

private:

    virtual QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    //	virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    //    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    //	virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    //	virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

    QPen    m_Pen;
    qreal   m_width;
    qreal   m_height;
    Handle  m_corner;
    QColor  m_color;
    Style   m_style;
    int     m_mouseButtonState;
    int     m_handleSize;


};


/*****************************************************************************************/


class HandleFrame : public QObject, public QGraphicsItem
{

    Q_OBJECT

public:
    HandleFrame(CanvasScene *scene, qreal grid = 1, int handleSize = 6);

    enum Type { Handle = UserType + 2 };

    // Properties
    int type() const { return Handle; }

    virtual QRectF boundingRect() const;
    virtual QRectF adjustedRect() const;
    QRectF selectionRect() const;
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

    void setColor(const QColor color);
    QColor color() const;

    void setItems(QList<AbstractItemBase*> list);

    int handleSize() const;
    void setGridSpace(int space);
    void setKeepAspectRatio(bool modifier);

    bool isHovered();
    bool canRotate();
    bool canHeightChange();

    // Members
    void updateHandles();
    void setup();
    void rotateSelection(qreal angle);




private:

    CanvasScene *	m_scene;
    QPointF     m_dragStart;
    int         m_gridSpace;
    int         m_rotationHandleDistance;
    QPointF     m_cornerDragStart;
    QRectF		m_oldRect;
    QPointF		m_oldPos;
    ItemHandle* m_handles[9];
    int         m_handleSize;
    bool		m_keepAspectRatio;
    QPen        m_pen;
    qreal       m_scaleFactor;
    QRectF		m_rect;
    qreal		m_ratio;
    bool		m_canHeightChange;
    bool        m_canWidthChange;
    bool		m_isHovered;
    QColor      m_color;
    bool        m_canRotate;
    QList<AbstractItemBase*> m_items;

    void adjustSize(qreal x, qreal y);
    void updateItemGeometry(AbstractItemBase *item);
    void updateItemsSelection();
    void reset();
    void sendSignals();
    bool selectionIsEmpty();
    qreal fitInGrid(qreal origin);

protected:
    // Events
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );// < allows the main object to be moved in the scene by capturing the mouse move events
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

    //	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;

public slots:
    void frameToSelection();

signals:
    void sendActiveItems(QList<AbstractItemBase *> items);
    void geometryChanged();

};


#endif // ITEMHANDLE_H
