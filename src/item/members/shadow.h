#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <abstractitemproperty.h>

class Shadow : public AbstractItemProperty
{
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset)
    Q_PROPERTY(qreal spread READ spread WRITE setSpread)

    Q_CLASSINFO("Version", "1.0.0")

public:
    // Constructor
    Shadow();
    Shadow(QString name, QColor color= QColor(0,0,0,128), qreal radius = 4, QPointF offset = QPointF(0,2), qreal spread = 0);
    Shadow(const Shadow &other);
    ~Shadow(){}

    bool operator==( const Shadow & other ) const;
    inline bool operator!=(const Shadow &shadow) const { return !(operator==(shadow)); }
    friend QDataStream &operator<<(QDataStream &out, const Shadow &obj);
    friend QDataStream &operator>>(QDataStream &in, Shadow &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Shadow &obj);
#endif

    // Properties
    void setColor(QColor color);
    QColor color() const;

    void setRadius(qreal radius);
    qreal radius() const;

    void setOffset(QPointF offset);
    void setOffset(qreal x, qreal y);
    QPointF offset() const;

    void setSpread(qreal spread);
    qreal spread() const;


private:
    QColor m_color;
    qreal m_radius;
    QPointF m_offset;
    qreal m_spread;

    void fromObject(AbstractItemProperty object);

};
Q_DECLARE_METATYPE(Shadow)


#endif // SHADOW_H
