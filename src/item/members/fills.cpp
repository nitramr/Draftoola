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
#include <QImageReader>
#include <QLinearGradient>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Fills::Fills() : Fills(QString()){}

Fills::Fills(const QString name) : Fills(name, Color()){}

// Color
Fills::Fills(const QString name, const Color &color) : AbstractItemProperty(name){
    m_gradient = Gradient();
    setColor(color);
    m_fillMode = FillMode::Fill;
    m_opacity = 1.0;
}

// Image (Path)
Fills::Fills(const QString name, const QString &path, const FillMode fillMode) :  Fills(name, Color()){
    setImagePath(path);
    m_fillMode = fillMode;
}

// Gradient
Fills::Fills(const QString name, const Gradient &gradient) : Fills(name, Color()){
    setGradient(gradient);
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
    m_color = color;
    setFillType(FillType::Color);
}

Color Fills::color() const
{
    return m_color;
}

void Fills::setImagePath(const QString path)
{
    m_imagePath = path;
    m_pixmap = QPixmap();
    setFillType(FillType::Image);
}

QString Fills::imagePath() const
{
    return m_imagePath;
}


QPixmap Fills::pixmap() const
{   
    if(m_pixmap.isNull()){
        QImageReader reader(m_imagePath);
        reader.setAutoTransform(true);
        return QPixmap::fromImageReader(&reader);
    }else return m_pixmap;
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
            m_imagePath == other.m_imagePath &&
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
           obj.imagePath() <<
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
        << obj.imagePath()
        << obj.opacity()
        << obj.gradient();

    return out;
}

QDataStream &operator>>(QDataStream &in, Fills &obj)
{
    AbstractItemProperty aip;
    Color color;
    Gradient gradient;
    QString imagePath;
    qreal opacity;
    int fillMode;
    int fillType;


    in >> aip >> fillType >> fillMode >> color >> imagePath >> opacity >> gradient;

    obj.fromObject(aip);
    obj.m_color = color;
    obj.m_opacity = opacity;
    obj.m_imagePath = imagePath;
    obj.m_fillMode = Fills::FillMode(fillMode);
    obj.m_fillType = FillType(fillType);
    obj.m_gradient = gradient;

    return in;
}
