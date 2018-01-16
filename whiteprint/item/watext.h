#ifndef WATEXT_H
#define WATEXT_H

#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

#include "itembase.h"


class WAText: public QGraphicsTextItem, public ItemBase
{
public:
	WAText(const QString &text, QGraphicsItem * parent = 0);
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = NULL);

	// Properties
	QRectF rect() const;
	void setRect(QRectF rect);

protected:
	virtual void focusOutEvent (QFocusEvent * event);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
	void SetTextInteraction(bool on, bool selectAll = false);
};

#endif // WATEXT_H
