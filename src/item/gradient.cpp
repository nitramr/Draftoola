#include "gradient.h"

Gradient::Gradient() : Gradient(QString()){}

Gradient::Gradient(QString name, GradientType type) : AbstractItemProperty (name)
{
    m_type = type;
}


Gradient::Gradient(const Gradient &other) : AbstractItemProperty(other)
{
    m_type = other.m_type;
}

bool Gradient::operator==(const Gradient &other) const
{
    if(this == &other) return true;

    return  m_type == other.m_type &&
            AbstractItemProperty::operator==(other);
}

QDebug operator<<(QDebug dbg, const Gradient &gradient)
{
    int gType = QVariant::fromValue(gradient.type()).value<int>();

    dbg << "Gradient(" <<
           "ID:" << gradient.ID() <<
           ", Name:" << gradient.name() <<
           ", Type:" << gType <<
           ", BlendMode:" << gradient.blendMode() <<
           ")";
    return dbg.maybeSpace();
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Gradient::setType(GradientType type){
    m_type = type;
}

GradientType Gradient::type() const{
    return m_type;
}


