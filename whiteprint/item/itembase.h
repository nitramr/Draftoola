#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QRectF>

#include "itemstruct.h"
#include "stroke.h"
#include "fills.h"
#include "gradient.h"

class ItemBase : public QGraphicsItem
{
public:

    ItemBase(QGraphicsItem *parent = 0);
    ItemBase(QRectF rect, QGraphicsItem *parent = 0);
	ItemBase(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = 0);

    // Properties
    void setName(QString name);
    QString name() const;
    void setItemType(ItemType type);
    ItemType itemType() const;
    virtual void setRect(QRectF rect);
    virtual QRectF rect() const;
	virtual QRectF rectAdjusted() const;
    virtual QRectF boundingRect() const;
	void setStroke(Stroke stroke);
	Stroke stroke() const;
	void setFills(Fills fills);
	Fills fills() const;
    qreal width() const;
    qreal height() const;

	// Members
	void addExportFactor(QString key, double value);
	void removeExportFactor(QString key);

    // Events
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
	// Properties
    QString m_name;
    ItemType m_itemType;
    QRectF m_rect;
    QRectF m_boundingRect;
	Stroke m_stroke;
	Fills m_fills;

	// Members
	QMap<QString, double> m_exportFactorList;

};

#endif // ITEMBASE_H
