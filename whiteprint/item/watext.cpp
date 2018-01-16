#include "watext.h"
#include <QPainter>
#include <QTextDocument>


WAText::WAText(const QString &text, QGraphicsItem *parent) : QGraphicsTextItem(text, parent)
{
	setPlainText("hello world");
	QFont f;
	f.setPointSize(20);
	f.setBold(true);
	f.setFamily("Helvetica");
	setFont(f);

	setFlags(QGraphicsItem::ItemIsMovable    |
			 QGraphicsItem::ItemIsFocusable  |
			 QGraphicsItem::ItemIsSelectable);
	setTextInteractionFlags(Qt::NoTextInteraction);
}

void WAText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setCompositionMode( QPainter::CompositionMode_SourceAtop );

	QGraphicsTextItem::paint(painter, option, widget);

}

QRectF WAText::rect() const
{
	return this->boundingRect();
//	return QRectF(this->pos().x(), this->pos().x(), this->document()->pageSize().width(), this->document()->pageSize().height());
}

void WAText::setRect(QRectF rect)
{
	this->setTextWidth(rect.width());
	this->document()->setPageSize(QSizeF(rect.width(), rect.height()));


}

void WAText::SetTextInteraction(bool on, bool selectAll)
{
	if(on && textInteractionFlags() == Qt::NoTextInteraction)
	{
		// switch on editor mode:
		setTextInteractionFlags(Qt::TextEditorInteraction);
		// manually do what a mouse click would do else:
		setFocus(Qt::MouseFocusReason); // this gives the item keyboard focus
		setSelected(true); // this ensures that itemChange() gets called when we click out of the item
		if(selectAll) // option to select the whole text (e.g. after creation of the TextItem)
		{
			QTextCursor c = textCursor();
			c.select(QTextCursor::Document);
			setTextCursor(c);
		}
	}
	else if(!on && textInteractionFlags() == Qt::TextEditorInteraction)
	{
		// turn off editor mode:
		setTextInteractionFlags(Qt::NoTextInteraction);
		// deselect text (else it keeps gray shade):
		QTextCursor c = this->textCursor();
		c.clearSelection();
		this->setTextCursor(c);
		clearFocus();
	}
}

QVariant WAText::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if(change == QGraphicsItem::ItemSelectedChange) qDebug("itemChange '%s', selected=%s", this->toPlainText().toStdString().c_str(), value.toString().toStdString().c_str());
	if(change == QGraphicsItem::ItemSelectedChange
		&& textInteractionFlags() != Qt::NoTextInteraction
		&& !value.toBool())
	{
		// item received SelectedChange event AND is in editor mode AND is about to be deselected:
		SetTextInteraction(false); // leave editor mode
	}
	return QGraphicsTextItem::itemChange(change, value);
}

void WAText::focusOutEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setTextInteractionFlags(Qt::NoTextInteraction);
}

void WAText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//	Q_UNUSED(event);
//	setTextInteractionFlags(Qt::TextEditable);
//	setFocus();

	qDebug("mouseDoubleClickEvent '%s'", this->toPlainText().toStdString().c_str());
	if(textInteractionFlags() == Qt::TextEditorInteraction)
	{
		// if editor mode is already on: pass double click events on to the editor:
		QGraphicsTextItem::mouseDoubleClickEvent(event);
		return;
	}

	// if editor mode is off:
	// 1. turn editor mode on and set selected and focused:
	SetTextInteraction(true);

	// 2. send a single click to this QGraphicsTextItem (this will set the cursor to the mouse position):
	// create a new mouse event with the same parameters as evt
	QGraphicsSceneMouseEvent *click = new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress);
	click->setButton(event->button());
	click->setPos(event->pos());
	QGraphicsTextItem::mousePressEvent(click);
	delete click; // don't forget to delete the event
}
