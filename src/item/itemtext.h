#ifndef ITEMTEXT_H
#define ITEMTEXT_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

#include "itembase.h"


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
    QGraphicsTextItem *m_text;
    QColor m_color;
    int m_lineHeight;

protected:
//	virtual void focusOutEvent (QFocusEvent * event);
//	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

//	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
//	void SetTextInteraction(bool on, bool selectAll = false);
};

#endif // WATEXT_H
