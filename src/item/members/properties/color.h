#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <abstractproperty.h>

class Color : public AbstractProperty, public QColor
{
public:
    // constructor
    Color();
    Color(const QColor &color);
    Color(const QString caption, QColor color);
    Color(double r, double g, double b, double a=255);
    Color(const QString caption, double r, double g, double b, double a=255);
    Color(const Color &other);

    // operator
    bool operator==( const Color & other ) const;
    inline bool operator!=(const Color &color) const { return !(operator==(color)); }
    friend QDataStream &operator<<(QDataStream &out, const Color &obj);
    friend QDataStream &operator>>(QDataStream &in, Color &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Color &obj);
#endif

private:
    void fromObject(AbstractProperty object);

};

#endif // COLOR_H
