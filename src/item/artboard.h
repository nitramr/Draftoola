#ifndef ARTBOARD_H
#define ARTBOARD_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QList>

#include <abstractitembase.h>

class Artboard;

class ArtboardLabel : public QGraphicsSimpleTextItem
{
public:
    ArtboardLabel(QString name, Artboard *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};


class Artboard : public AbstractItemBase
{
public:
    Artboard();
    Artboard(QString name, QGraphicsItem *parent = nullptr);
    Artboard(QString name, QRectF rect, QGraphicsItem *parent = nullptr);
    Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    Artboard(const Artboard &other);

    // Properties
    int type() const override { return Type::Artboard; }

	QGraphicsRectItem *canvas() const;
    void setRect(QRectF rect) override;
    QRectF renderRect() const override;

    void setBackgroundColor(const QColor color);
    QColor backgroundColor() const;

    void setUseBackgroundColor(bool useBGColor);
    bool useBackgroundColor() const;

    void addItem(AbstractItemBase *item) override;
    QList<AbstractItemBase *> childItems() const override;

    void setName(QString text) override;

    // operator
    bool operator==( const Artboard & other ) const;
    inline bool operator!=(const Artboard &itemBase) const;
    friend QDataStream &operator<<(QDataStream &out, const Artboard &obj);
    friend QDataStream &operator>>(QDataStream &in, Artboard &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Artboard &obj);
#endif


private:
    int m_offset;
    int m_buffer;    
    bool m_useBGColor;
    QColor m_backgroundColor;
    ArtboardLabel * m_label;
	QGraphicsRectItem * m_artboard;

    void fromObject(AbstractItemBase *obj);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ARTBOARD_H
