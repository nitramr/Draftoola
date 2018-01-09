#ifndef WATEXT_H
#define WATEXT_H

#include <QGraphicsTextItem>


class WAText: public QGraphicsTextItem
{
public:
	WAText(const QString &text, QGraphicsItem * parent = 0);
//	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = NULL);

protected:
	virtual void focusOutEvent (QFocusEvent * event);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
};

#endif // WATEXT_H
