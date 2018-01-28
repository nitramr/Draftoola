#include "stroke.h"

Stroke::Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition ) : QPen(style),
	m_name(name), m_strokePosition(strokePosition){}
Stroke::Stroke(const QString name, const QColor &color, const StrokePosition strokePosition ) : QPen(color),
	m_name(name), m_strokePosition(strokePosition){}
Stroke::Stroke(const QString name, const QBrush &brush, qreal width, const StrokePosition strokePosition , Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) : QPen(brush, width, style, cap, join),
	m_name(name), m_strokePosition(strokePosition){}
Stroke::Stroke(const QString name, const QPen &pen, const StrokePosition strokePosition ) : QPen(pen),
	m_name(name), m_strokePosition(strokePosition){}


/***************************************************
 *
 * Properties
 *
 ***************************************************/


QString Stroke::name() const{
	return m_name;
}

void Stroke::setStrokePosition(StrokePosition position)
{
	m_strokePosition = position;
}

StrokePosition Stroke::strokePosition() const
{
	return m_strokePosition;
}

