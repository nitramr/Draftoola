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

#include "fills.h"
#include <QDebug>
#include <QLinearGradient>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Fills::Fills() : Fills(QString()){}

Fills::Fills(const QString name) : Fills(name, Color()){}

Fills::Fills(const QString name, const Color &color) : AbstractItemProperty(name){
    m_gradient = Gradient();
    setColor(color);
    m_type = Type::Fill;
    m_fillMode = FillMode::Fill;
}

Fills::Fills(const QString name, const QPixmap &pixmap, const FillMode fillMode) :  Fills(name, Color()){
    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const QImage &image, const FillMode fillMode) : Fills(name, Color()){

    QPixmap pixmap(image.size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.drawImage(0,0,image);
    painter.end();

    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const Gradient &gradient) : Fills(name, Color()){
    setGradient(gradient);
    m_fillMode = FillMode::Fill;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Fills::setFillType(FillType filltype)
{
    m_fillType = filltype;
}

FillType Fills::fillType() const
{
    return m_fillType;
}

void Fills::setFillMode(FillMode fillMode)
{
    m_fillMode = fillMode;
}

Fills::FillMode Fills::fillMode() const
{
    return m_fillMode;
}

void Fills::setGradient(Gradient gradient)
{
    m_gradient = gradient;
    setFillType(m_gradient.type());
}

Gradient Fills::gradient() const
{
    return m_gradient;
}

void Fills::setColor(Color color)
{
    qreal opacity = qRound(color.alphaF() * 100) / 100.0;
    setOpacity(opacity);

    if(opacity < 1.0) color.setAlphaF(1);

    m_color = color;

    setFillType(FillType::Color);
}

Color Fills::color() const
{
    return m_color;
}

void Fills::setPixmap(QPixmap pixmap)
{
    m_pixmap = pixmap;
    setFillType(FillType::Image);
}

QPixmap Fills::pixmap() const
{
    return m_pixmap;
}

void Fills::setOpacity(qreal opacity)
{
    m_opacity = qMax(0.0, qMin(1.0, opacity)); //clamp values
}

qreal Fills::opacity() const
{
    return m_opacity;
}

void Fills::fromObject(AbstractItemProperty object)
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

bool Fills::operator==(const Fills &other) const
{
    return  m_fillType == other.m_fillType &&
            m_fillMode == other.m_fillMode &&
            m_gradient == other.m_gradient &&
            m_color == other.m_color &&
            m_pixmap.toImage() == other.m_pixmap.toImage() &&
            m_opacity == other.m_opacity &&
            AbstractItemProperty::operator==(other);
}

QDebug operator<<(QDebug dbg, const Fills &obj)
{
    const AbstractItemProperty &aip = obj;

    dbg << "Fills(" <<
           aip <<
           (int)obj.fillType() <<
           (int)obj.fillMode() <<
           obj.gradient() <<
           obj.color() <<
           obj.pixmap() <<
           obj.opacity() <<
           ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Fills &obj)
{
    const AbstractItemProperty &aip = obj;

    out << aip
        << (int)obj.fillType()
        << (int)obj.fillMode()
        << obj.color()
        << obj.pixmap()
        << obj.opacity()
        << obj.gradient();

    return out;
}

QDataStream &operator>>(QDataStream &in, Fills &obj)
{
    AbstractItemProperty aip;
    Color color;
    Gradient gradient;
    QPixmap pixmap;
    qreal opacity;
    int fillMode;
    int fillType;


    in >> aip >> fillType >> fillMode >> color >> pixmap >> opacity >> gradient;

    obj.fromObject(aip);
    obj.m_color = color;
    obj.m_opacity = opacity;
    obj.m_pixmap = pixmap;
    obj.m_fillMode = Fills::FillMode(fillMode);
    obj.m_fillType = FillType(fillType);
    obj.m_gradient = gradient;

    return in;
}
