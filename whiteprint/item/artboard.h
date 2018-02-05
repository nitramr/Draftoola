#ifndef ARTBOARD_H
#define ARTBOARD_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QString>
#include "itembase.h"

class Artboard;

class ArtboardLabel : public QGraphicsTextItem
{
public:
	ArtboardLabel(QString name, Artboard *parent);
//	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	virtual void focusOutEvent (QFocusEvent * event);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

};


class Artboard : /*public QGraphicsRectItem, */public ItemBase
{
public:
    Artboard(QString name, QGraphicsItem *parent = 0);
    Artboard(QString name, QRectF rect, QGraphicsItem *parent = 0);
    Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = 0);

    // Properties
	QGraphicsRectItem *canvas() const;
	virtual void setRect(QRectF rect);
	virtual QRectF rect() const ;
	virtual QRectF boundingRect() const;

private:
	QGraphicsDropShadowEffect * m_shadow;
    int m_offset;
    int m_buffer;
    QRectF m_rect;
    QRectF m_boundingRect;
    ArtboardLabel * m_label;
	QGraphicsRectItem * m_artboard;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

};

#endif // ARTBOARD_H
