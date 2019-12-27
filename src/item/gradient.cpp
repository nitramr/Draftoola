#include "gradient.h"

Gradient::Gradient() : Gradient(QString()){}

Gradient::Gradient(QString name, GradientType type) : AbstractItemProperty (name)
{
    m_type = type;
}


Gradient::Gradient(const Gradient &other)
{
    m_id = other.m_id;
    m_name = other.m_name;
    m_type = other.m_type;
    m_blendMode = other.m_blendMode;
}

bool Gradient::operator==(const Gradient &other) const
{
    return m_id == other.m_id &&
            m_name == other.m_name &&
            m_type == other.m_type &&
            m_blendMode == other.m_blendMode;
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


