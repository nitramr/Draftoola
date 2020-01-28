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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};


class ArtboardCanvas : public QGraphicsRectItem
{

public:
    enum Type {
        Canvas = UserType + 1
    };

   int type() const override
   {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type::Canvas;
   }

   inline ArtboardCanvas(QRectF rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent){}

};


class Artboard : public AbstractItemBase
{
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QRect rect READ rect WRITE setRect)
    Q_PROPERTY(bool useBackgroundColor READ useBackgroundColor WRITE setUseBackgroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

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
    ArtboardCanvas * m_artboard;

    void fromObject(AbstractItemBase *obj);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ARTBOARD_H
