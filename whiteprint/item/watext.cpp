#include "watext.h"

WAText::WAText(const QString &text, QGraphicsItem *parent) : QGraphicsTextItem(text, parent)
{
//	setPlainText("hello world");
//	QFont f;
//	f.setPointSize(50);
//	f.setBold(true);
//	f.setFamily("Helvetica");
//	setFont(f);

	setFlags(QGraphicsItem::ItemIsMovable    |
			 QGraphicsItem::ItemIsFocusable /* |
			 QGraphicsItem::ItemIsSelectable*/);
	setTextInteractionFlags(Qt::NoTextInteraction);
}

//void WAText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//	QGraphicsTextItem::paint(painter, option, widget);
//}

void WAText::focusOutEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setTextInteractionFlags(Qt::NoTextInteraction);
}

void WAText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event);
	setTextInteractionFlags(Qt::TextEditable);
	setFocus();
}
