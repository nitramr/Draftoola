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

#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <abstractproperty.h>

class Color : public AbstractProperty, public QColor
{
public:
    // constructor
    Color();
    Color(const QColor &color);
    Color(const QString caption, QColor color);
    Color(double r, double g, double b, double a=255);
    Color(const QString caption, double r, double g, double b, double a=255);
    Color(const Color &other);

    // operator
    Color &operator=(const Color &) = default;
    bool operator==( const Color & other ) const;
    inline bool operator!=(const Color &color) const { return !(operator==(color)); }
    friend QDataStream &operator<<(QDataStream &out, const Color &obj);
    friend QDataStream &operator>>(QDataStream &in, Color &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Color &obj);
#endif

private:
    void fromObject(AbstractProperty object);

};

#endif // COLOR_H
