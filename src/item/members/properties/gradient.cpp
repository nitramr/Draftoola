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

#include "gradient.h"

Gradient::Gradient() : Gradient(QString(), QLinearGradient()){}
Gradient::Gradient(const Gradient &other) : AbstractProperty(other){
    m_stops = other.m_stops;
    m_angle = other.m_angle;
    m_spread = other.m_spread;
    m_cmode = other.m_cmode;
    m_imode = other.m_imode;
    m_start = other.m_start;
    m_stop = other.m_stop;
    m_center = other.m_center;
    m_radius = other.m_radius;
    m_type = other.m_type;
    m_focal = other.m_focal;
}

Gradient::Gradient(QString name, const QGradient &gradient) : AbstractProperty (name)
{
    m_stops = gradient.stops();
    m_spread = gradient.spread();
    m_cmode = gradient.coordinateMode();
    m_imode = gradient.interpolationMode();
    m_angle = 0.0;
    m_start = QPointF();
    m_stop = QPointF(100,100);
    m_focal = m_start;
    m_center = m_start;
    m_radius = -1;

    switch(gradient.type()){
    default:
    case QGradient::LinearGradient:
        m_type = FillType::LinearGradient;
        m_start = static_cast<const QLinearGradient *>(&gradient)->start();
        m_stop = static_cast<const QLinearGradient *>(&gradient)->finalStop();
        break;
    case QGradient::RadialGradient:
        m_type = FillType::RadialGradient;
        m_center = static_cast<const QRadialGradient *>(&gradient)->center();
        m_focal = static_cast<const QRadialGradient *>(&gradient)->focalPoint();
        m_radius = (double)static_cast<const QRadialGradient *>(&gradient)->radius();
        break;
    case QGradient::ConicalGradient:
        m_type = FillType::ConicalGradient;
        m_center = static_cast<const QConicalGradient *>(&gradient)->center();
        m_angle = (double) static_cast<const QConicalGradient *>(&gradient)->angle();
        break;
    }
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/


QRadialGradient Gradient::radial(QRectF target) const
{
    QPointF center = (target.isNull()) ? m_center : target.center();
    QPointF focal = (target.isNull()) ? m_focal : target.center();
    qreal radius = (m_radius == -1) ? ( (target.width() <= target.height()) ? target.width() / 2 : target.height() / 2) : m_radius;

    QRadialGradient rg(center, radius, focal);
    rg.setStops(m_stops);
    rg.setSpread(m_spread);
    rg.setCoordinateMode(m_cmode);
    rg.setInterpolationMode(m_imode);
    return rg;
}

QLinearGradient Gradient::linear(QLineF target) const
{
    QPointF start = (target.isNull()) ? m_start : target.p1();
    QPointF stop = (target.isNull()) ? m_stop : target.p2();

    QLinearGradient lg(start, stop);
    lg.setStops(m_stops);
    lg.setSpread(m_spread);
    lg.setCoordinateMode(m_cmode);
    lg.setInterpolationMode(m_imode);
    return lg;
}

QConicalGradient Gradient::conical(QRectF target) const
{
    QPointF center = (target.isNull()) ? m_center : target.center();

    QConicalGradient cg(center, m_angle);
    cg.setStops(m_stops);
    cg.setSpread(m_spread);
    cg.setCoordinateMode(m_cmode);
    cg.setInterpolationMode(m_imode);
    return cg;
}

FillType Gradient::type()
{
    return m_type;
}

QGradientStops Gradient::stops() const
{
    return m_stops;
}

void Gradient::setStops(QGradientStops stops)
{
    m_stops = stops;
}

qreal Gradient::angle() const
{
    return m_angle;
}

void Gradient::setAngle(qreal angle)
{
    m_angle = angle;
}

QGradient::Spread Gradient::spread() const
{
    return m_spread;
}

void Gradient::setSpread(QGradient::Spread spread)
{
    m_spread = spread;
}

QGradient::CoordinateMode Gradient::coordinateMode() const
{
    return m_cmode;
}

void Gradient::setCoordinateMode(QGradient::CoordinateMode cmode)
{
    m_cmode = cmode;
}

QGradient::InterpolationMode Gradient::interpolationMode() const
{
    return m_imode;
}

void Gradient::setInterpolationMode(QGradient::InterpolationMode imode)
{
    m_imode = imode;
}

QPointF Gradient::center() const
{
    return m_center;
}

void Gradient::setCenter(QPointF center)
{
    m_center = center;
}

QPointF Gradient::start() const
{
    return m_start;
}

void Gradient::setStart(QPointF start)
{
    m_start = start;
}

QPointF Gradient::finalStop() const
{
    return m_stop;
}

void Gradient::setFinalStop(QPointF stop)
{
    m_stop = stop;
}

QPointF Gradient::focalPoint() const
{
    return m_focal;
}

void Gradient::setFocalPoint(QPointF focal)
{
    m_focal = focal;
}

qreal Gradient::radius() const
{
    return m_radius;
}

void Gradient::setRadius(qreal radius)
{
    m_radius = radius;
}

void Gradient::fromObject(AbstractProperty object)
{
    m_id = object.m_id;
    m_caption = object.m_caption;
}


/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool Gradient::operator==(const Gradient &other) const
{
    if(this == &other) return true;

    return  AbstractProperty::operator==(other) &&
            m_stops == other.m_stops &&
            m_angle == other.m_angle &&
            m_spread == other.m_spread &&
            m_cmode == other.m_cmode &&
            m_imode == other.m_imode &&
            m_start == other.m_start &&
            m_stop == other.m_stop &&
            m_center == other.m_center &&
            m_radius == other.m_radius;
}


QDebug operator<<(QDebug dbg, const Gradient &obj)
{

    const AbstractProperty &ap = obj;

    dbg << "Gradient("
        << ap
        << int(obj.m_type)
        << obj.m_start
        << obj.m_stop
        << obj.m_center
        << obj.m_focal
        << (double)obj.m_radius
        << obj.m_center
        << (double)obj.m_angle
        << ")";

    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Gradient &obj)
{
    const AbstractProperty &ap = obj;

    out << ap
        << int(obj.m_type)
        << int(obj.m_spread)
        << int(obj.m_cmode)
        << int(obj.m_imode);

    if (sizeof(qreal) == sizeof(double)) {
        out << obj.m_stops;
    } else {
        // ensure that we write doubles here instead of streaming the stops
        // directly; otherwise, platforms that redefine qreal might generate
        // data that cannot be read on other platforms.
        QVector<QGradientStop> stops = obj.m_stops;
        out << quint32(stops.size());
        for (int i = 0; i < stops.size(); ++i) {
            const QGradientStop &stop = stops.at(i);
            out << QPair<double, QColor>(double(stop.first), stop.second);
        }
    }

    out << obj.m_start
        << obj.m_stop
        << obj.m_center
        << obj.m_focal
        << (double)obj.m_radius
        << obj.m_center
        << (double)obj.m_angle;

    return out;
}

QDataStream &operator>>(QDataStream &in, Gradient &obj)
{

    AbstractProperty m_ap;
    in >> m_ap;

    obj.fromObject(m_ap);

    int type_as_int = 0;

    in >> type_as_int;
    obj.m_type = FillType(type_as_int);

    in >> type_as_int;
    obj.m_spread = QGradient::Spread(type_as_int);

    in >> type_as_int;
    obj.m_cmode = QGradient::CoordinateMode(type_as_int);

    in >> type_as_int;
    obj.m_imode = QGradient::InterpolationMode(type_as_int);

    QGradientStops stops;
    if (sizeof(qreal) == sizeof(double)) {
        in >> stops;
    } else {
        quint32 numStops;
        double n;
        QColor c;
        in >> numStops;
        stops.reserve(numStops);
        for (quint32 i = 0; i < numStops; ++i) {
            in >> n >> c;
            stops << QPair<qreal, QColor>(n, c);
        }
    }

    obj.m_stops = stops;

    in >> obj.m_start;
    in >> obj.m_stop;
    in >> obj.m_center;
    in >> obj.m_focal;
    in >> obj.m_radius;
    in >> obj.m_center;
    in >> obj.m_angle;

    return in;
}
