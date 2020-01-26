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

#ifndef STROKE_H
#define STROKE_H


#include <QColor>
#include <QString>
#include <QPen>
#include <QPainter>
#include <QDebug>

#include <utilities.h>
#include <abstractitemproperty.h>

class Stroke : public QPen, public AbstractItemProperty
{
 //   Q_GADGET
public:

    enum StrokePosition {
        Center = 0,
        Inner = 1,
        Outer = 2
    };

    Stroke();
    Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition = StrokePosition::Center);
    Stroke(const QString name, const QColor & color, const StrokePosition strokePosition = StrokePosition::Center);
    Stroke(const QString name, const QBrush & brush, qreal width, const StrokePosition strokePosition = StrokePosition::Center, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
    Stroke(const QString name, const QPen & pen, const StrokePosition strokePosition = StrokePosition::Center);
//    Stroke(const Stroke &other);
    Stroke(const Stroke &) = default;

    ~Stroke() = default;

    Stroke &operator=(const Stroke &) = default;
    bool operator==( const Stroke & other ) const;
    inline bool operator!=(const Stroke &stroke) const { return !(operator==(stroke)); }
    friend QDataStream &operator<<(QDataStream &out, const Stroke &obj);
    friend QDataStream &operator>>(QDataStream &in, Stroke &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Stroke &obj);
#endif

	// Properties
	void setStrokePosition(StrokePosition position);
	StrokePosition strokePosition() const;



private:
	StrokePosition m_strokePosition;

    void fromObject(AbstractItemProperty object, QPen pen);

};
Q_DECLARE_METATYPE(Stroke)
Q_DECLARE_METATYPE(Stroke::StrokePosition)

#endif // STROKE_H
