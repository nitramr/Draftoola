#ifndef ARTBOARD_H
#define ARTBOARD_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QString>
#include "abstractitembase.h"

class Artboard;

class ArtboardLabel : public QGraphicsTextItem
{
public:
	ArtboardLabel(QString name, Artboard *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	virtual void focusOutEvent (QFocusEvent * event);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

};


class Artboard : public AbstractItemBase
{
public:
    Artboard(QString name, QGraphicsItem *parent = nullptr);
    Artboard(QString name, QRectF rect, QGraphicsItem *parent = nullptr);
    Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    // Properties
	QGraphicsRectItem *canvas() const;
    void setRect(QRectF rect);
    void addItem(AbstractItemBase *item);

private:
    int m_offset;
    int m_buffer;
    ArtboardLabel * m_label;
	QGraphicsRectItem * m_artboard;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // ARTBOARD_H
