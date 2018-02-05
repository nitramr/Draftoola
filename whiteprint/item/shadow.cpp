#include "shadow.h"

Shadow::Shadow(QColor color, qreal radius, QPointF offset, qreal spread)
{
	setColor(color);
	setRadius(radius);
	setOffset(offset);
	setSpread(spread);
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

void Shadow::setSpread(qreal spread)
{
	m_spread = spread;
}

qreal Shadow::spread() const
{
	return m_spread;
}
