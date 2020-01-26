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

#include "color.h"

#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Color::Color() : Color(QColor(Qt::black)){}
Color::Color(const QString name, QColor color) : AbstractProperty(name), QColor(color){}
Color::Color(double r, double g, double b, double a) : Color(QColor(r,g,b,a)){}
Color::Color(const QString name, double r, double g, double b, double a): Color(name, QColor(r,g,b,a)){}
Color::Color(const Color &other) : AbstractProperty(other), QColor(other){}
Color::Color(const QColor &color) : Color(QString(),color)
{
    m_caption = color.name();
}

/***************************************************
 *
 * Member
 *
 ***************************************************/

void Color::fromObject(AbstractProperty object)
{
    m_id = object.m_id;
    m_caption = object.m_caption;
}

/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool Color::operator==(const Color &other) const
{
    return  AbstractProperty::operator==(other) &&
            QColor::operator==(other);
}


QDebug operator<<(QDebug dbg, const Color &obj)
{
    const AbstractProperty &aip = obj;
    const QColor &col = obj;

    dbg << "Color(" <<
           aip <<
           col <<
           ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Color &obj)
{
    const AbstractProperty &ap = obj;
    const QColor &col = obj;

    out << ap
        << col;

    return out;
}

QDataStream &operator>>(QDataStream &in, Color &obj)
{
    AbstractProperty m_ap;
    QColor color;

    in >> m_ap >> color;

    obj.fromObject(m_ap);

    switch(color.spec()){
    default:
    case QColor::Rgb:
        obj.setRgbF(color.redF(),color.greenF(),color.blueF(),color.alphaF());
        break;
    case QColor::Hsv:
        obj.setHsvF(color.hueF(),color.saturationF(),color.valueF(),color.alphaF());
        break;
    case QColor::Cmyk:
        obj.setCmykF(color.cyanF(),color.magentaF(),color.yellowF(),color.blackF());
        break;
    case QColor::Hsl:
        obj.setHslF(color.hueF(),color.saturationF(),color.lightnessF(),color.alphaF());
        break;
    case QColor::Invalid:
        obj.setRgb(Qt::black);
        break;
    }

    return in;
}

