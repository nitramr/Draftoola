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

    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn)
    Q_CLASSINFO("Version", "1.0.0")

public:
    AbstractItemProperty();
    AbstractItemProperty(const QString name, QPainter::CompositionMode compositionMode = QPainter::CompositionMode_SourceOver, bool isOn = true);
    AbstractItemProperty(const AbstractItemProperty &other);

    // operator
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


private:
    QString m_id;
    QString m_name;
    QPainter::CompositionMode m_blendMode;
    bool m_isOn;


};
Q_DECLARE_METATYPE(AbstractItemProperty)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const AbstractItemProperty &shadow);
#endif

//QDataStream &operator<<(QDataStream &out, const AbstractItemProperty &obj);
//QDataStream &operator>>(QDataStream &in, AbstractItemProperty &obj);

#endif // ABSTRACTITEMPROPERTY_H
