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


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void AbstractItemProperty::setID(QString id)
{
    m_id = id;
}

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
