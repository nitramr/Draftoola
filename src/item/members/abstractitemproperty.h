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

#ifndef ABSTRACTITEMPROPERTY_H
#define ABSTRACTITEMPROPERTY_H

#include <QString>
#include <QPainter>

class AbstractItemProperty
{

    friend class Fills;
    friend class Stroke;
    friend class Gradient;
    friend class Shadow;
    friend class ExportLevel;

    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn)
    Q_PROPERTY(QPainter::CompositionMode blendMode READ blendMode WRITE setBlendMode)

public:

    enum Type {
        Fill = 0,
        Stroke = 1,
        Shadow = 2
    };

    AbstractItemProperty();
    AbstractItemProperty(const QString name, QPainter::CompositionMode compositionMode = QPainter::CompositionMode_SourceOver, bool isOn = true);
//    AbstractItemProperty(const AbstractItemProperty &other);
    AbstractItemProperty(const AbstractItemProperty &) = default;

    ~AbstractItemProperty() = default;

    // operator
    AbstractItemProperty &operator=(const AbstractItemProperty &) = default;
    bool operator==( const AbstractItemProperty & other ) const;
    inline bool operator!=(const AbstractItemProperty &other) const { return !(operator==(other)); }
    friend QDataStream &operator<<(QDataStream &out, const AbstractItemProperty &obj);
    friend QDataStream &operator>>(QDataStream &in, AbstractItemProperty &obj);


    // Properties
    void setID(const QString id);
    QString ID() const;

    void setName(const QString name);
    QString name() const;

    void setBlendMode(QPainter::CompositionMode compositionMode);
    QPainter::CompositionMode blendMode() const;

    void setIsOn(bool isOn);
    bool isOn() const;

    Type type() const;


private:
    QString m_id;
    QString m_name;
    QPainter::CompositionMode m_blendMode;
    bool m_isOn;
    Type m_type;



};
Q_DECLARE_METATYPE(AbstractItemProperty)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const AbstractItemProperty &obj);
#endif

//QDataStream &operator<<(QDataStream &out, const AbstractItemProperty &obj);
//QDataStream &operator>>(QDataStream &in, AbstractItemProperty &obj);

#endif // ABSTRACTITEMPROPERTY_H
