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

bool AbstractItemProperty::operator==(const AbstractItemProperty &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_name == other.m_name &&
            m_blendMode == other.m_blendMode &&
            m_isOn == other.m_isOn;
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

void AbstractItemProperty::setName(QString name)
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
