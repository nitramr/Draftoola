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

#ifndef ABSTRACTPROPERTY_H
#define ABSTRACTPROPERTY_H

#include <QString>
#include <QObject>

class AbstractProperty
{

    friend class Gradient;
    friend class ExportLevel;
    friend class Color;

    Q_CLASSINFO("Version", "1.0.0")

public:
    AbstractProperty();
    AbstractProperty(const QString caption);
    AbstractProperty(const AbstractProperty &other);

    // operator
    bool operator==( const AbstractProperty & other ) const;
    inline bool operator!=(const AbstractProperty &other) const { return !(operator==(other)); }
    friend QDataStream &operator<<(QDataStream &out, const AbstractProperty &obj);
    friend QDataStream &operator>>(QDataStream &in, AbstractProperty &obj);


    // Properties
    void setID(const QString id);
    QString ID() const;

    void setCaption(const QString caption);
    QString caption() const;

private:
    QString m_id;
    QString m_caption;

};
Q_DECLARE_METATYPE(AbstractProperty)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const AbstractProperty &shadow);
#endif

#endif // ABSTRACTPROPERTY_H
