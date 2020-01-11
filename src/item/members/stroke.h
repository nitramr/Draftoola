#ifndef STROKE_H
#define STROKE_H


#include <QColor>
#include <QString>
#include <QPen>
#include <QPainter>
#include <QDebug>

#include <itemstruct.h>
#include <abstractitemproperty.h>

class Stroke : public QPen, public AbstractItemProperty
{
 //   Q_GADGET
public:

    enum StrokePosition {
        Center = 0,
        Inner = 1,
        Outer = 2
    };

    Stroke();
    Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition = StrokePosition::Center);
    Stroke(const QString name, const QColor & color, const StrokePosition strokePosition = StrokePosition::Center);
    Stroke(const QString name, const QBrush & brush, qreal width, const StrokePosition strokePosition = StrokePosition::Center, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
    Stroke(const QString name, const QPen & pen, const StrokePosition strokePosition = StrokePosition::Center);

    Stroke(const Stroke &other);
    ~Stroke(){}

    bool operator==( const Stroke & other ) const;
    inline bool operator!=(const Stroke &stroke) const { return !(operator==(stroke)); }
    friend QDataStream &operator<<(QDataStream &out, const Stroke &obj);
    friend QDataStream &operator>>(QDataStream &in, Stroke &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Stroke &obj);
#endif

	// Properties
	void setStrokePosition(StrokePosition position);
	StrokePosition strokePosition() const;



private:
	StrokePosition m_strokePosition;

    void fromObject(AbstractItemProperty object, QPen pen);

};
Q_DECLARE_METATYPE(Stroke)
Q_DECLARE_METATYPE(Stroke::StrokePosition)

#endif // STROKE_H
