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

#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <abstractitemproperty.h>

class Shadow : public AbstractItemProperty
{
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset)
    Q_PROPERTY(qreal spread READ spread WRITE setSpread)

    Q_CLASSINFO("Version", "1.0.0")

public:
    // Constructor
    Shadow();
    Shadow(QString name, QColor color= QColor(0,0,0,128), qreal radius = 4, QPointF offset = QPointF(0,2), qreal spread = 0);
//    Shadow(const Shadow &other);
    Shadow(const Shadow &) = default;

    ~Shadow() = default;

    Shadow &operator=(const Shadow &) = default;
    bool operator==( const Shadow & other ) const;
    inline bool operator!=(const Shadow &shadow) const { return !(operator==(shadow)); }
    friend QDataStream &operator<<(QDataStream &out, const Shadow &obj);
    friend QDataStream &operator>>(QDataStream &in, Shadow &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Shadow &obj);
#endif

    // Properties
    void setColor(QColor color);
    QColor color() const;

    void setRadius(qreal radius);
    qreal radius() const;

    void setOffset(QPointF offset);
    void setOffset(qreal x, qreal y);
    QPointF offset() const;

    void setSpread(qreal spread);
    qreal spread() const;


private:
    QColor m_color;
    qreal m_radius;
    QPointF m_offset;
    qreal m_spread;

    void fromObject(AbstractItemProperty object);

};
Q_DECLARE_METATYPE(Shadow)


#endif // SHADOW_H
