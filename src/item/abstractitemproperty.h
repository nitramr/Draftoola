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

public:
    AbstractItemProperty();
    AbstractItemProperty(const QString name, QPainter::CompositionMode compositionMode = QPainter::CompositionMode_SourceOver, bool isOn = true);
    AbstractItemProperty(const AbstractItemProperty &other);

    // operator
    bool operator==( const AbstractItemProperty & other ) const;
    inline bool operator!=(const AbstractItemProperty &other) const { return !(operator==(other)); }


    // Properties
    QString ID() const;

    void setName(QString name);
    QString name() const;

    void setBlendMode(QPainter::CompositionMode compositionMode);
    QPainter::CompositionMode blendMode() const;

    void setIsOn(bool isOn);
    bool isOn() const;

private:
    QString m_id;
    QString m_name;
    QPainter::CompositionMode m_blendMode;
    bool m_isOn;


};

#endif // ABSTRACTITEMPROPERTY_H
