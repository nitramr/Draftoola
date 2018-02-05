#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>

class Shadow
{
public:
	Shadow(QColor color= QColor(0,0,0,128), qreal radius = 4, QPointF offset = QPointF(0,2), qreal spread = 0);

	// Properties
	void setColor(QColor color);
	QColor color() const;
	void setRadius(qreal radius);
	qreal radius() const;
	void setOffset(QPointF offset);
	void setOffset(qreal x, qreal y);
	QPointF offset() const;
	void setSpread(qreal spread);
	qreal spread() const;


private:
	QColor m_color;
	qreal m_radius;
	QPointF m_offset;
	qreal m_spread;

};

#endif // SHADOW_H
