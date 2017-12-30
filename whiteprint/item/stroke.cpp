#include "stroke.h"

Stroke::Stroke(const QString name, Qt::PenStyle style) : QPen(style), m_name(name){}
Stroke::Stroke(const QString name, const QColor &color) : QPen(color), m_name(name){}
Stroke::Stroke(const QString name, const QBrush &brush, qreal width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) : QPen(brush, width, style, cap, join), m_name(name){}
Stroke::Stroke(const QString name, const QPen &pen) : QPen(pen), m_name(name){}


/***************************************************
 *
 * Properties
 *
 ***************************************************/


QString Stroke::name() const{
	return m_name;
}

