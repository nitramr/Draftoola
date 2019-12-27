#include "shadow.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Shadow::Shadow() : Shadow(QString::null){}

Shadow::Shadow(QString name, QColor color, qreal radius, QPointF offset, qreal spread) : AbstractItemProperty(name)
{
    setColor(color);
    setRadius(radius);
    setOffset(offset);
    setSpread(spread);
}

Shadow::Shadow(const Shadow &other)
{
    m_id = other.m_id;
    m_name = other.m_name;
    m_color = other.m_color;
    m_radius = other.m_radius;
    m_offset = other.m_offset;
    m_spread = other.m_spread;
    m_blendMode = other.m_blendMode;
    m_isOn = other.m_isOn;
}

bool Shadow::operator==(const Shadow &other) const
{
    return m_id == other.m_id &&
            m_name == other.m_name &&
            m_color == other.m_color &&
            m_radius == other.m_radius &&
            m_offset == other.m_offset &&
            m_spread == other.m_spread &&
            m_blendMode == other.m_blendMode &&
            m_isOn == other.m_isOn;
}

QDebug operator<<(QDebug dbg, const Shadow &shadow)
{

    dbg << "Shadow( ID:" << shadow.ID() <<
           ", Name:" << shadow.name() <<
           ", Color:" << shadow.color() <<
           ", Radius:" << shadow.radius() <<
           ", Offset:" << shadow.offset() <<
           ", Spread:" << shadow.spread() <<
           ", BlendMode:" << shadow.blendMode() <<
           ", IsOn:" << shadow.isOn() <<
           ")";
    return dbg.maybeSpace();
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/


void Shadow::setColor(QColor color)
{
    m_color = color;
}

QColor Shadow::color() const
{
    return m_color;
}

void Shadow::setRadius(qreal radius)
{
    m_radius = radius;
}

qreal Shadow::radius() const
{
    return m_radius;
}

void Shadow::setOffset(QPointF offset)
{
    m_offset = offset;
}

void Shadow::setOffset(qreal x, qreal y)
{
    setOffset(QPointF(x,y));
}

QPointF Shadow::offset() const
{
    return m_offset;
}

void Shadow::setSpread(qreal spread)
{
    m_spread = spread;
}

qreal Shadow::spread() const
{
    return m_spread;
}
