#ifndef STROKE_H
#define STROKE_H


#include <QColor>
#include <QString>
#include <QPen>
#include <QPainter>
#include <QDebug>

#include "itemstruct.h"
#include "abstractitemproperty.h"

class Stroke : public QPen, public AbstractItemProperty
{
 //   Q_GADGET
public:

    Stroke();
    Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition = StrokePosition::Inner);
    Stroke(const QString name, const QColor & color, const StrokePosition strokePosition = StrokePosition::Inner);
    Stroke(const QString name, const QBrush & brush, qreal width, const StrokePosition strokePosition = StrokePosition::Inner, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
    Stroke(const QString name, const QPen & pen, const StrokePosition strokePosition = StrokePosition::Inner);

    Stroke(const Stroke &other);
    ~Stroke(){}

    bool operator==( const Stroke & other ) const;
    inline bool operator!=(const Stroke &stroke) const { return !(operator==(stroke)); }

	// Properties
	void setStrokePosition(StrokePosition position);
	StrokePosition strokePosition() const;


private:
	StrokePosition m_strokePosition;

};
Q_DECLARE_METATYPE(Stroke)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Stroke &stroke);
#endif

#endif // STROKE_H
