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
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

	// Properties
    void setRect(QRectF rect);

	void setText(const QString text);
	QString text() const;

	void setFont(const QFont font);
	QFont font() const;

	void setFontSize(int pixelSize);
	int fontSize() const;

    void setTextColor(const QColor color);
    QColor textColor() const;

    void setFrameFitText(bool doFit );
    bool frameFitText();

    void setAligmnet(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void setLineHeight(qreal lineHeight);
    qreal lineHeight() const;


private:
	QGraphicsTextItem *m_text;
    bool m_frameFitText;
    QColor m_color;

protected:
//	virtual void focusOutEvent (QFocusEvent * event);
//	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

//	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
//	void SetTextInteraction(bool on, bool selectAll = false);
};

#endif // WATEXT_H
