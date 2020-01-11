#ifndef ABSTRACTPROPERTY_H
#define ABSTRACTPROPERTY_H

#include <QString>
#include <QObject>

class AbstractProperty
{

    friend class Gradient;
    friend class ExportLevel;
    friend class Color;

    Q_CLASSINFO("Version", "1.0.0")

public:
    AbstractProperty();
    AbstractProperty(const QString caption);
    AbstractProperty(const AbstractProperty &other);

    // operator
    bool operator==( const AbstractProperty & other ) const;
    inline bool operator!=(const AbstractProperty &other) const { return !(operator==(other)); }
    friend QDataStream &operator<<(QDataStream &out, const AbstractProperty &obj);
    friend QDataStream &operator>>(QDataStream &in, AbstractProperty &obj);


    // Properties
    void setID(const QString id);
    QString ID() const;

    void setCaption(const QString caption);
    QString caption() const;

private:
    QString m_id;
    QString m_caption;

};
Q_DECLARE_METATYPE(AbstractProperty)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const AbstractProperty &shadow);
#endif

#endif // ABSTRACTPROPERTY_H
