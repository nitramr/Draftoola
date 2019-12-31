#include "itemtext.h"
#include <QPainter>
#include <QTextDocument>
#include <QDebug>
#include <QTextFrame>
#include <QStyleOptionGraphicsItem>



ItemText::ItemText(const QString &text, QGraphicsItem *parent) : ItemBase(QRectF(), parent)
{
    QFont f;
    f.setPixelSize(16);
    f.setBold(false);
    f.setFamily("Helvetica");

    m_frameFitText = true;
    m_lineHeight = f.pixelSize() * 1.2;

    m_text = new QGraphicsTextItem(text);
    setFont(f);
    setTextColor(QColor(0,0,0));
    setAlignment(Qt::AlignLeft);
    setText(text);
    setRect(m_text->boundingRect());
    this->setName(tr("Text"));

    this->setItemType(ItemType::Text);

    //	setTextInteractionFlags(Qt::NoTextInteraction);


}

void ItemText::setRect(QRectF rect)
{

    m_text->setTextWidth(rect.width());
    if(frameFitText()) rect = m_text->boundingRect();

    QPainterPath path;
    path.addRect(rect);
    setShape(path);
}

void ItemText::setText(const QString text)
{    

    m_text->document()->setHtml("<p style='line-height:"+ QString::number(m_lineHeight) +"px;'>"+text+"</p>");

}

QString ItemText::text() const
{
    return m_text->document()->toPlainText();
}

void ItemText::setFont(const QFont font)
{
    m_text->setFont(font);
}

QFont ItemText::font() const
{
    return m_text->font();
}

void ItemText::setFontSize(int pixelSize)
{
    m_text->font().setPixelSize(pixelSize);
}

int ItemText::fontSize() const
{
    return m_text->font().pixelSize();
}

void ItemText::setTextColor(const QColor color)
{
    m_text->setDefaultTextColor(color);
}

QColor ItemText::textColor() const
{
    return m_text->defaultTextColor();
}

void ItemText::setFrameFitText(bool doFit)
{
    m_frameFitText = doFit;
}

bool ItemText::frameFitText()
{
    return m_frameFitText;
}

void ItemText::setAlignment(Qt::Alignment alignment)
{
    QTextOption option(alignment);
    m_text->document()->setDefaultTextOption(option);
}

Qt::Alignment ItemText::alignment() const
{
    return m_text->document()->defaultTextOption().alignment();
}

void ItemText::setLineHeight(qreal lineHeight)
{

    m_lineHeight = lineHeight;

//    QTextDocument* doc = m_text->document();
//    QTextFrame * root = doc->rootFrame();
//    QTextFrame::iterator it;
//    for( it = root->begin(); !(it.atEnd()); ++it )
//    {
//        QTextBlock block = it.currentBlock();
//        qDebug() << "setLineheight" << block.blockFormat().lineHeight();
//        block.blockFormat().setLineHeight(100, QTextBlockFormat::LineDistanceHeight); //https://doc.qt.io/qt-5/qtextblockformat.html#LineHeightTypes-enum
//        //block.blockFormat().setLineHeight(lineHeight, QTextBlockFormat::FixedHeight);
//        qDebug() << "setLineheight";
//    }

}

qreal ItemText::lineHeight() const
{
    return m_lineHeight;
}

//void WAText::SetTextInteraction(bool on, bool selectAll)
//{
//	if(on && textInteractionFlags() == Qt::NoTextInteraction)
//	{
//		// switch on editor mode:
//		setTextInteractionFlags(Qt::TextEditorInteraction);
//		// manually do what a mouse click would do else:
//		setFocus(Qt::MouseFocusReason); // this gives the item keyboard focus
//		setSelected(true); // this ensures that itemChange() gets called when we click out of the item
//		if(selectAll) // option to select the whole text (e.g. after creation of the TextItem)
//		{
//			QTextCursor c = textCursor();
//			c.select(QTextCursor::Document);
//			setTextCursor(c);
//		}
//	}
//	else if(!on && textInteractionFlags() == Qt::TextEditorInteraction)
//	{
//		// turn off editor mode:
//		setTextInteractionFlags(Qt::NoTextInteraction);
//		// deselect text (else it keeps gray shade):
//		QTextCursor c = this->textCursor();
//		c.clearSelection();
//		this->setTextCursor(c);
//		clearFocus();
//	}
//}

//QVariant WAText::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//	if(change == QGraphicsItem::ItemSelectedChange) qDebug("itemChange '%s', selected=%s", this->toPlainText().toStdString().c_str(), value.toString().toStdString().c_str());
//	if(change == QGraphicsItem::ItemSelectedChange
//		&& textInteractionFlags() != Qt::NoTextInteraction
//		&& !value.toBool())
//	{
//		// item received SelectedChange event AND is in editor mode AND is about to be deselected:
//		SetTextInteraction(false); // leave editor mode
//	}
//	return QGraphicsTextItem::itemChange(change, value);
//}

//void WAText::focusOutEvent(QFocusEvent *event)
//{
//	Q_UNUSED(event);
//	setTextInteractionFlags(Qt::NoTextInteraction);
//}

//void WAText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
////	Q_UNUSED(event);
////	setTextInteractionFlags(Qt::TextEditable);
////	setFocus();

//	qDebug("mouseDoubleClickEvent '%s'", this->toPlainText().toStdString().c_str());
//	if(textInteractionFlags() == Qt::TextEditorInteraction)
//	{
//		// if editor mode is already on: pass double click events on to the editor:
//		QGraphicsTextItem::mouseDoubleClickEvent(event);
//		return;
//	}

//	// if editor mode is off:
//	// 1. turn editor mode on and set selected and focused:
//	SetTextInteraction(true);

//	// 2. send a single click to this QGraphicsTextItem (this will set the cursor to the mouse position):
//	// create a new mouse event with the same parameters as evt
//	QGraphicsSceneMouseEvent *click = new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress);
//	click->setButton(event->button());
//	click->setPos(event->pos());
//	QGraphicsTextItem::mousePressEvent(click);
//	delete click; // don't forget to delete the event
//}

void ItemText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ItemBase::paint(painter, option, widget);

    // reset painter state, like select, edit etc.
    QStyleOptionGraphicsItem *opt = new QStyleOptionGraphicsItem();

    m_text->paint(painter, opt, widget);


}
