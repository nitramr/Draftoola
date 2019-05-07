#include "stroke.h"

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Stroke::Stroke() : Stroke(QString::null, QPen()){}

Stroke::Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition ) : QPen(style), AbstractItemProperty(name){
   setStrokePosition(strokePosition);
}
Stroke::Stroke(const QString name, const QColor &color, const StrokePosition strokePosition ) : QPen(color), AbstractItemProperty(name){
   setStrokePosition(strokePosition);
}
Stroke::Stroke(const QString name, const QBrush &brush, qreal width, const StrokePosition strokePosition , Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) : QPen(brush, width, style, cap, join), AbstractItemProperty(name){
   setStrokePosition(strokePosition);
}
Stroke::Stroke(const QString name, const QPen &pen, const StrokePosition strokePosition ) : QPen(pen), AbstractItemProperty(name){
    setStrokePosition(strokePosition);
}

Stroke::Stroke(const Stroke &other)
{
    setID(other.ID());
    setName(other.name());
    setStrokePosition(other.strokePosition());

//    setColor(other.color());
    setDashOffset(other.dashOffset());
    setDashPattern(other.dashPattern());
    setWidthF(other.widthF());
    setBrush(other.brush());
    setStyle(other.style());
    setCapStyle(other.capStyle());
    setJoinStyle(other.joinStyle());
    setBlendMode(other.blendMode());
    setIsOn(other.isOn());
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Stroke::setStrokePosition(StrokePosition position)
{
    m_strokePosition = position;
}

StrokePosition Stroke::strokePosition() const
{
    return m_strokePosition;
}

