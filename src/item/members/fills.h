#ifndef FILLS_H
#define FILLS_H

#include <QBrush>
#include <QGradient>
#include <QPixmap>
#include <QColor>
#include <QPainter>

#include <itemstruct.h>
#include <abstractitemproperty.h>
#include <gradient.h>
#include <color.h>

class Fills : public AbstractItemProperty
{

     Q_CLASSINFO("Version", "1.0.0")

public:

    enum FillMode {
        Fill = 0,
        Fit = 1,
        Stretch = 2,
        Tile = 3
    };


    // Constructor
    Fills();
    Fills(const QString name);
    Fills(const QString name, const Color & color);
    Fills(const QString name, const QPixmap & pixmap, const FillMode fillMode = FillMode::Fill);
    Fills(const QString name, const QImage & image, const FillMode fillMode = FillMode::Fill);
    Fills(const QString name, const Gradient & gradient);
    Fills(const Fills &other);
    virtual ~Fills(){}


    // Properties
    void setFillType(FillType filltype);
    FillType fillType() const;

    void setFillMode(FillMode fillMode);
    FillMode fillMode() const;

    void setGradient(Gradient gradient);
    virtual Gradient gradient() const;

    void setColor(Color color);
    Color color() const;

    void setPixmap(QPixmap pixmap);
    QPixmap pixmap() const;

    void setOpacity(int opacity);
    int opacity() const;


    bool operator==( const Fills & other ) const;
    inline bool operator!=(const Fills &fill) const { return !(operator==(fill)); }
    friend QDataStream &operator<<(QDataStream &out, const Fills &obj);
    friend QDataStream &operator>>(QDataStream &in, Fills &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Fills &obj);
#endif

private:

    FillType m_fillType = FillType::Color;
    FillMode m_fillMode = FillMode::Fill;
    Gradient m_gradient;
    Color m_color;
    QPixmap m_pixmap;
    int m_opacity;

    void fromObject(AbstractItemProperty object);

};
Q_DECLARE_METATYPE(Fills)
Q_DECLARE_METATYPE(Fills::FillMode)

#endif // FILLS_H
