/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include <itemtext.h>
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTextBlockFormat>
#include <qabstracttextdocumentlayout.h>



ItemText::ItemText(const QString &text, QGraphicsItem *parent) : ItemBase(QRectF(), parent)
{
    QFont f;
    f.setPixelSize(16);
    f.setBold(false);
    f.setFamily("Helvetica");

    m_lineHeight = f.pixelSize() * 1.2;

    m_text = new QTextDocument(text);
    m_text->setUseDesignMetrics(true);
    m_color = Qt::black;

    setFont(f);
    //setTextColor(QColor(0,0,0));
    setAlignment(Qt::AlignLeft);
    setText(text);
    setRect(QRectF(0,0,m_text->idealWidth(), m_text->size().height()));
    setName(tr("Text"));

    //	setTextInteractionFlags(Qt::NoTextInteraction);


}

ItemText::ItemText(const ItemText &other) : ItemBase(other)
{
    m_text = other.m_text;
    m_color = other.m_color;
    m_lineHeight = other.m_lineHeight;
}

bool ItemText::operator==(const ItemText &other) const
{
    if(this == &other) return true;

    return m_text == other.m_text &&
            m_color == other.m_color &&
            m_lineHeight == other.m_lineHeight &&
            ItemBase::operator==(other);
}

void ItemText::setRect(QRectF rect)
{

    m_text->setTextWidth(rect.width());

    switch(frameType()){
    case AbstractItemBase::FixedWidth:
        // rect = m_text->boundingRect();
        break;
    case AbstractItemBase::FixedHeight:

        break;
    case AbstractItemBase::FixedSize:
        rect = this->rect();
        break;
    case AbstractItemBase::Free:
        break;
    }



    //    QPainterPath path;
    //    QFont f_font(font());
    //    f_font.setStyleStrategy(QFont::ForceOutline);
    //    path.addText(0, 0, f_font, text());

    QPainterPath path;
    path.addRect(rect);
    ItemBase::setShape(path);

    calculateRenderRect();
}

void ItemText::setText(const QString text)
{    

    //   m_text->setHtml("<p style='line-height:"+ QString::number(m_lineHeight) +"px;'>"+text+"</p>");
    m_text->setMarkdown("# Headline\n\rHello World\n\r**second** *line*", QTextDocument::MarkdownDialectGitHub);

}

QString ItemText::text() const
{
    return m_text->toPlainText();
}

void ItemText::setFont(const QFont font)
{
    m_text->setDefaultFont(font);
}

QFont ItemText::font() const
{
    return m_text->defaultFont();
}

void ItemText::setFontSize(int pixelSize)
{
    m_text->defaultFont().setPixelSize(pixelSize);
}

int ItemText::fontSize() const
{
    return m_text->defaultFont().pixelSize();
}

void ItemText::setTextColor(const QColor color)
{

    //    m_text->firstBlock().blockFormat().setForeground(QBrush(color));
    m_color = color;
}

QColor ItemText::textColor() const
{
    //  return m_text->firstBlock().blockFormat().foreground().color();
    return m_color;
}

void ItemText::setAlignment(Qt::Alignment alignment)
{
    QTextOption option(alignment);
    m_text->setDefaultTextOption(option);
}

Qt::Alignment ItemText::alignment() const
{
    return m_text->defaultTextOption().alignment();
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


void ItemText::refreshFrame()
{
    //   QTextFrame format(m_text);

    QTextFrameFormat frameFormat(m_text->rootFrame()->frameFormat());
    frameFormat.setPadding(10);




    //    QTextBlockFormat blockFormat(m_text->firstBlock().blockFormat());
    //    blockFormat.setLineHeight(30, QTextBlockFormat::FixedHeight);
    //    blockFormat.setTextIndent(0);

    QTextCharFormat charFormat;
    charFormat.setFontWeight(8);

    QTextCursor cursor (m_text);
    cursor.select (QTextCursor::Document);
//    cursor.mergeCharFormat (charFormat);
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    cursor.selectionStart();
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor.selectionEnd();
    cursor.setCharFormat(charFormat);

    m_text->rootFrame()->setFrameFormat(frameFormat);

    QTextBlockFormat blockFormat(m_text->firstBlock().blockFormat());
    blockFormat.setLineHeight(100, QTextBlockFormat::FixedHeight);


    for (QTextBlock it = m_text->begin(); it != m_text->end(); it = it.next()){
         qDebug() << it.text();
         it.blockFormat().setLineHeight(10, QTextBlockFormat::FixedHeight);
    }


    QAbstractTextDocumentLayout *layout = m_text->documentLayout();
    qDebug() << layout->blockBoundingRect(m_text->firstBlock());

    // https://doc.qt.io/qt-5/qtextformat.html#Property-enum
    //    format.setProperty(0x1048, m_lineHeight);

    //    format.property(QTextFormat::LineHeight);

    //    QTextCharFormat format;
    //    //          format.setTextOutline (QPen (Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)); // Color and width of outline

    //              QTextCursor cursor (m_text);
    //              cursor.select (QTextCursor::Document);
    //              cursor.mergeCharFormat (format);
    //              m_text->document()->drawContents(painter, rect());
    //              format.setTextOutline (QPen (Qt::transparent));




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

    painter->save();

    //    if(m_lod < 0.6 && !m_doRender){

    ////        QTextCharFormat charFormat;
    ////        charFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    ////        charFormat.setUnderlineColor(Qt::red);

    ////        QTextCursor cur = m_text->document()->find("Hello");
    ////        cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    ////        cur.selectionStart();
    ////        cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    ////        cur.selectionEnd();
    ////        cur.setCharFormat(charFormat);


    //        QTextCharFormat format;
    //          format.setTextOutline (QPen (Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)); // Color and width of outline

    //          QTextCursor cursor (m_text->document());
    //          cursor.select (QTextCursor::Document);
    //          cursor.mergeCharFormat (format);
    //          m_text->document()->drawContents(painter, rect());
    //          format.setTextOutline (QPen (Qt::transparent));
    //          cursor.mergeCharFormat (format);
    //          m_text->document()->drawContents(painter, rect());


    // //       painter->save();
    ////       painter->translate(opt->rect.x(), opt->rect.y());
    //  //      m_text->document()->drawContents(painter, rect());
    // //       painter->restore();



    //    }else m_text->document()->drawContents(painter, rect());


    /***
     *  https://doc.qt.io/archives/qt-4.8/qtextlayout.html
     *  https://doc.qt.io/archives/qq/qq24-textlayouts.html
     *
     */


    //    painter->setBrush(QBrush(Qt::black));
    //    m_textLayout.draw(painter, QPoint(0, 0));

    //    QAbstractTextDocumentLayout::Selection selection;
    ////      selection.cursor = textCursor();
    ////      selection.format = textCursor().charFormat();

    //      QAbstractTextDocumentLayout::PaintContext ctx;
    //      ctx.palette.setColor(QPalette::Text, m_color);
    //      //ctx.cursorPosition = textCursor().position();
    //      ctx.selections.append(selection);
    //      ctx.clip.setRect(0,0, rect().width(), rect().height());


    //      m_text->documentLayout()->draw(painter,ctx);

 //  refreshFrame();


    m_text->drawContents(painter, rect());

    painter->restore();

}


