#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>

class Shadow
{
public:
	Shadow(QColor color= QColor(0,0,0,128), qreal radius = 0, QPointF offset = QPointF(0,2));

	// Properties
	void setColor(QColor color);
	QColor color() const;
	void setRadius(qreal radius);
	qreal radius() const;
	void setOffset(QPointF offset);
	void setOffset(qreal x, qreal y);
	QPointF offset() const;

private:
	QColor m_color;
	qreal m_radius;
	QPointF m_offset;

};

#endif // SHADOW_H
