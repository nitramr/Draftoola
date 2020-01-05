#ifndef ARTBOARD_H
#define ARTBOARD_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QList>
#include "abstractitembase.h"

class Artboard;

class ArtboardLabel : public QGraphicsSimpleTextItem
{
public:
    ArtboardLabel(QString name, Artboard *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};


class Artboard : public AbstractItemBase
{
public:
    Artboard(QString name, QGraphicsItem *parent = nullptr);
    Artboard(QString name, QRectF rect, QGraphicsItem *parent = nullptr);
    Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    // Properties
    int type() const override { return Type::Artboard; }

	QGraphicsRectItem *canvas() const;
    void setRect(QRectF rect);
    QRectF renderRect() const override;

    void setBackgroundColor(const QColor color);
    QColor backgroundColor() const;

    void setUseBackgroundColor(bool useBGColor);
    bool useBackgroundColor() const;

    void addItem(AbstractItemBase *item) override;
    QList<AbstractItemBase *> childItems() override;


private:
    int m_offset;
    int m_buffer;    
    bool m_useBGColor;
    QColor m_backgroundColor;
    ArtboardLabel * m_label;
	QGraphicsRectItem * m_artboard;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ARTBOARD_H
