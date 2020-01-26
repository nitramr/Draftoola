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

#include "abstractproperty.h"
#include <QRandomGenerator>
#include <QDebug>

AbstractProperty::AbstractProperty() : AbstractProperty(QString()) {}
AbstractProperty::AbstractProperty(const QString name)
{
    QRandomGenerator *random = QRandomGenerator::global();
    quint32 value32 = random->generate();
    QString hexvalue = QString("0x%1").arg(value32, 8, 16, QLatin1Char( '0' ));

    m_id = hexvalue; //static_cast<int>(value32);
    m_caption = name;
}

AbstractProperty::AbstractProperty(const AbstractProperty &other)
{
    m_id = other.m_id;
    m_caption = other.m_caption;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QString AbstractProperty::ID() const
{
    return m_id;
}

void AbstractProperty::setCaption(const QString name)
{
    m_caption = name;
}

QString AbstractProperty::caption() const{
    return m_caption;
}


/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool AbstractProperty::operator==(const AbstractProperty &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_caption == other.m_caption;
}

void AbstractProperty::setID(const QString id)
{
    m_id = id;
}

QDebug operator<<(QDebug dbg, const AbstractProperty &obj)
{
    dbg << obj.ID() <<
           obj.caption();
    return dbg.maybeSpace();
}


QDataStream &operator<<(QDataStream &out, const AbstractProperty &obj)
{
    out << obj.ID()
       << obj.caption();

    return out;
}

QDataStream &operator>>(QDataStream &in, AbstractProperty &obj)
{
    in >> obj.m_id;
    in >> obj.m_caption;

    return in;
}

