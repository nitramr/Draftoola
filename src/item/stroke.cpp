#include "stroke.h"

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Stroke::Stroke() : Stroke(QString::null, QPen()){}
Stroke::Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition ) : Stroke(name, QPen(style), strokePosition){}
Stroke::Stroke(const QString name, const QColor &color, const StrokePosition strokePosition ) : Stroke(name, QBrush(color), 1, strokePosition, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin){}
Stroke::Stroke(const QString name, const QBrush &brush, qreal width, const StrokePosition strokePosition , Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) : QPen(brush, width, style, cap, join), AbstractItemProperty(name){
   setStrokePosition(strokePosition);
   setMiterLimit(0);
}
Stroke::Stroke(const QString name, const QPen &pen, const StrokePosition strokePosition ) : QPen(pen), AbstractItemProperty(name){
    setStrokePosition(strokePosition);
    setMiterLimit(0);
}

/*!
 * \brief Assigns the given stroke to this stroke and returns a reference to this stroke.
 * \param other
 */
Stroke::Stroke(const Stroke &other) : QPen(other), AbstractItemProperty(other)
{
    m_strokePosition = other.m_strokePosition;
}


bool Stroke::operator==(const Stroke &other) const
{
    if(this == &other) return true;

    return m_strokePosition == other.m_strokePosition &&
            AbstractItemProperty::operator==(other) &&
            QPen::operator==(other);

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

