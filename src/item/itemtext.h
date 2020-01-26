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

#ifndef ITEMTEXT_H
#define ITEMTEXT_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QTextLayout>
#include <QTextDocument>

#include <itembase.h>


class ItemText: public ItemBase
{
public:
    ItemText(const QString &text, QGraphicsItem * parent = nullptr);
    ItemText(const ItemText &other);


    // operator
    bool operator==( const ItemText & other ) const;
    inline bool operator!=(const ItemText &itemBase) const;


    // Properties
    int type() const override { return Type::Text; }

    void setRect(QRectF rect) override;

    void setText(const QString text);
    QString text() const;

    void setFont(const QFont font);
    QFont font() const;

    void setFontSize(int pixelSize);
    int fontSize() const;

    void setTextColor(const QColor color);
    QColor textColor() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void setLineHeight(qreal lineHeight);
    qreal lineHeight() const;

    // Events
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
//    QGraphicsTextItem *m_text;
    QTextDocument * m_text;
    QColor m_color;
    int m_lineHeight;

    void refreshFrame();

//    QList<QTextLayout *> layouts;
//    QStringList paragraphs;
//    QList<QList<QTextLayout::FormatRange> > formats;

protected:
    //	virtual void focusOutEvent (QFocusEvent * event);
    //	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

    //	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    //	void SetTextInteraction(bool on, bool selectAll = false);
};

#endif // WATEXT_H
