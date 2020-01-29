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
#include <color.h>

#include <utilities.h>
#include <abstractitemproperty.h>
#include <gradient.h>

class Stroke : public AbstractItemProperty
{
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(StrokePosition strokePosition READ strokePosition WRITE setStrokePosition)

public:

    enum StrokePosition {
        Center = 0,
        Inner = 1,
        Outer = 2
    };

    Stroke();
    Stroke(const QString name, const Color & color, qreal width = 1.0, const StrokePosition strokePosition = StrokePosition::Center, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
    Stroke(const QString name, const Gradient & gradient, qreal width = 1.0, const StrokePosition strokePosition = StrokePosition::Center, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
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
    Type type() const override{
        return Type::Stroke;
    };

	void setStrokePosition(StrokePosition position);
	StrokePosition strokePosition() const;

    void setColor(Color color);
    Color color() const;

    void setGradient(Gradient gradient);
    Gradient gradient() const;

    void setStyle(Qt::PenStyle style);
    Qt::PenStyle style() const;

    void setCapStyle(Qt::PenCapStyle cap);
    Qt::PenCapStyle capStyle() const;

    void setJoinStyle(Qt::PenJoinStyle joinStyle);
    Qt::PenJoinStyle joinStyle() const;

    void setWidthF(qreal width);
    qreal widthF() const;

    void setWidth(int width);
    int width() const;

    QPen pen() const;

    void setFillType(FillType fillType);
    FillType fillType() const;

private:
    Color m_color;
    Gradient m_gradient;
    Qt::PenStyle m_style;
    Qt::PenCapStyle m_cap;
    Qt::PenJoinStyle m_join;
    qreal m_width;
    FillType m_fillType;



private:
	StrokePosition m_strokePosition;

    void fromObject(AbstractItemProperty object);

};
Q_DECLARE_METATYPE(Stroke)
Q_DECLARE_METATYPE(Stroke::StrokePosition)

#endif // STROKE_H
