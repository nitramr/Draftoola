#include "gradient.h"

Gradient::Gradient() : Gradient(QString()){}

Gradient::Gradient(QString name, GradientType type) : AbstractItemProperty (name)
{
    m_type = type;
}


Gradient::Gradient(const Gradient &other)
{
    setID(other.ID());
    setName(other.name());
    setType(other.type());
    setBlendMode(other.blendMode());
}

bool Gradient::operator==(const Gradient &other) const
{
    return ID() == other.ID() &&
            name() == other.name() &&
            type() == other.type() &&
            blendMode() == other.blendMode();
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


