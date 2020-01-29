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

#include "stroke.h"

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Stroke::Stroke() : Stroke(QString(), QColor()){}
Stroke::Stroke(const QString name, const Color &color, qreal width, const Stroke::StrokePosition strokePosition, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join)
    : AbstractItemProperty(name)
{
    m_gradient = Gradient();
    m_color = color;
    m_width = width;
    m_strokePosition = strokePosition;
    m_style = style;
    m_cap = cap;
    m_join = join;
    m_fillType = FillType::Color;
}

Stroke::Stroke(const QString name, const Gradient &gradient, qreal width, const Stroke::StrokePosition strokePosition, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join)
    :AbstractItemProperty(name)
{
    m_gradient = gradient;
    m_color = Color();
    m_width = width;
    m_strokePosition = strokePosition;
    m_style = style;
    m_cap = cap;
    m_join = join;
    m_fillType = gradient.type();
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Stroke::setStrokePosition(StrokePosition position)
{
    m_strokePosition = position;
}

Stroke::StrokePosition Stroke::strokePosition() const
{
    return m_strokePosition;
}

void Stroke::setColor(Color color)
{
    m_color = color;
    m_fillType = FillType::Color;
}

Color Stroke::color() const
{
    return m_color;
}

void Stroke::setGradient(Gradient gradient)
{
    m_gradient = gradient;
    m_fillType = gradient.type();
}

Gradient Stroke::gradient() const
{
    return m_gradient;
}

void Stroke::setStyle(Qt::PenStyle style)
{
    m_style = style;
}

Qt::PenStyle Stroke::style() const
{
    return m_style;
}

void Stroke::setCapStyle(Qt::PenCapStyle cap)
{
    m_cap = cap;
}

Qt::PenCapStyle Stroke::capStyle() const
{
    return m_cap;
}

void Stroke::setJoinStyle(Qt::PenJoinStyle joinStyle)
{
    m_join = joinStyle;
}

Qt::PenJoinStyle Stroke::joinStyle() const
{
    return m_join;
}

void Stroke::setWidthF(qreal width)
{
    m_width = width;
}

qreal Stroke::widthF() const
{
    return m_width;
}

void Stroke::setWidth(int width)
{
    setWidthF(width);
}

int Stroke::width() const
{
    return qRound(m_width);
}

QPen Stroke::pen() const
{
    QBrush brush;

    switch(m_fillType){
    case FillType::LinearGradient:
        brush = QBrush(m_gradient.linear());
        break;
    case FillType::RadialGradient:
        brush = QBrush(m_gradient.radial());
        break;
    case FillType::ConicalGradient:
        brush = QBrush(m_gradient.conical());
        break;
    case FillType::Color:
        brush = QBrush(m_color);
        break;
    default:
        brush = QBrush(Qt::black);
        break;
    }

   return QPen(brush, m_width, m_style, m_cap, m_join);

}

void Stroke::setFillType(FillType fillType)
{
    m_fillType = fillType;
}

FillType Stroke::fillType() const
{
    return m_fillType;
}

void Stroke::fromObject(AbstractItemProperty object)
{
    m_id = object.m_id;
    m_isOn = object.m_isOn;
    m_blendMode = object.m_blendMode;
    m_name = object.m_name;
}


/***************************************************
 *
 * Operator
 *
 ***************************************************/


bool Stroke::operator==(const Stroke &other) const
{
    if(this == &other) return true;

    return m_strokePosition == other.m_strokePosition &&
            m_width == other.m_width &&
            m_cap == other.m_cap &&
            m_join == other.m_join &&
            m_style == other.m_style &&
            m_color == other.m_color &&
            m_gradient == other.m_gradient &&
            m_fillType == other.m_fillType &&
            AbstractItemProperty::operator==(other);

}


QDebug operator<<(QDebug dbg, const Stroke &obj)
{
    const AbstractItemProperty &aip = obj;

    dbg << "Stroke(" <<
           aip <<
           (int)obj.strokePosition() <<
           obj.widthF();

    switch(obj.fillType()){
    default:
    case FillType::Color:
        dbg << obj.color();
        break;
    case FillType::LinearGradient:
    case FillType::RadialGradient:
    case FillType::ConicalGradient:
        dbg << obj.gradient();
        break;
    }

    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Stroke &obj)
{
    const AbstractItemProperty &aip = obj;

    out << aip<<
           (int)obj.strokePosition() <<
           obj.widthF() <<
           (int)obj.capStyle() <<
           (int)obj.joinStyle() <<
           (int)obj.style() <<
           obj.color() <<
           obj.gradient() <<
           (int)obj.fillType();

    return out;
}

QDataStream &operator>>(QDataStream &in, Stroke &obj)
{
    AbstractItemProperty m_aip;
    int m_strokePos;
    Color m_color;
    Gradient m_gradient;
    int m_style;
    int m_cap;
    int m_join;
    qreal m_width;
    int m_fillType;

    in >> m_aip;
    in >> m_strokePos;
    in >> m_width;
    in >> m_cap;
    in >> m_join;
    in >> m_style;
    in >> m_color;
    in >> m_gradient;
    in >> m_fillType;

    obj.fromObject(m_aip);
    obj.setStrokePosition(Stroke::StrokePosition(m_strokePos));
    obj.setWidthF(m_width);
    obj.setCapStyle(Qt::PenCapStyle(m_cap));
    obj.setJoinStyle(Qt::PenJoinStyle(m_join));
    obj.setStyle(Qt::PenStyle(m_style));
    obj.setGradient(m_gradient);
    obj.setColor(m_color);
    obj.setFillType(FillType(m_fillType));


    return in;
}
