#include "shadow.h"

Shadow::Shadow(QColor color, qreal radius, QPointF offset)
{
	m_color = color;
	m_radius = radius;
	m_offset = offset;
}

void Shadow::setColor(QColor color)
{
	m_color = color;
}

QColor Shadow::color() const
{
	return m_color;
}

void Shadow::setRadius(qreal radius)
{
	m_radius = radius;
}

qreal Shadow::radius() const
{
	return m_radius;
}

void Shadow::setOffset(QPointF offset)
{
	m_offset = offset;
}

void Shadow::setOffset(qreal x, qreal y)
{
	setOffset(QPointF(x,y));
}

QPointF Shadow::offset() const
{
	return m_offset;
}
