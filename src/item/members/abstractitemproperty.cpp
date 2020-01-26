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

#include "abstractitemproperty.h"
#include <QRandomGenerator>
#include <QDebug>

AbstractItemProperty::AbstractItemProperty() : AbstractItemProperty(QString()) {}

AbstractItemProperty::AbstractItemProperty(const QString name , QPainter::CompositionMode compositionMode, bool isOn )
{

    QRandomGenerator *random = QRandomGenerator::global();
    quint32 value32 = random->generate();
    QString hexvalue = QString("0x%1").arg(value32, 8, 16, QLatin1Char( '0' ));

    m_id = hexvalue; //static_cast<int>(value32);
    m_name = name;
    m_blendMode = compositionMode;
    m_isOn = isOn;
}

AbstractItemProperty::AbstractItemProperty(const AbstractItemProperty &other)
{
    m_id = other.m_id;
    m_name = other.m_name;
    m_blendMode = other.m_blendMode;
    m_isOn = other.m_isOn;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QString AbstractItemProperty::ID() const
{
    return m_id;
}

void AbstractItemProperty::setName(const QString name)
{
    m_name = name;
}

QString AbstractItemProperty::name() const{
    return m_name;
}


void AbstractItemProperty::setBlendMode(QPainter::CompositionMode compositionMode)
{
    m_blendMode = compositionMode;
}

QPainter::CompositionMode AbstractItemProperty::blendMode() const
{
    return m_blendMode;
}

void AbstractItemProperty::setIsOn(bool isOn)
{
    m_isOn = isOn;
}

bool AbstractItemProperty::isOn() const
{
    return m_isOn;
}



/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool AbstractItemProperty::operator==(const AbstractItemProperty &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_name == other.m_name &&
            m_blendMode == other.m_blendMode &&
            m_isOn == other.m_isOn;
}

void AbstractItemProperty::setID(const QString id)
{
    m_id = id;
}

QDebug operator<<(QDebug dbg, const AbstractItemProperty &obj)
{
    dbg << obj.ID() <<
           obj.name() <<
           obj.blendMode() <<
           obj.isOn();
    return dbg.maybeSpace();
}


QDataStream &operator<<(QDataStream &out, const AbstractItemProperty &obj)
{
    out << obj.ID()
       << obj.name()
       << (int)obj.blendMode()
       << obj.isOn();

    return out;
}

QDataStream &operator>>(QDataStream &in, AbstractItemProperty &obj)
{
    QString m_id;
    QString m_name;
    int m_blendMode;
    bool m_isOn;

    in >> m_id >> m_name >> m_blendMode >> m_isOn;

    obj.m_isOn = m_isOn;
    obj.m_name = m_name;
    obj.m_blendMode = QPainter::CompositionMode(m_blendMode);
    obj.m_id = m_id;

    return in;
}

