#ifndef ITEMEFFECTS_H
#define ITEMEFFECTS_H

#include <QGraphicsEffect>
#include "shadow.h"
#include "fills.h"

class ItemEffects : public QGraphicsEffect
{
public:
	ItemEffects(QObject *parent = 0);
	QRectF boundingRectFor(const QRectF &rect) const;

	void setShadowList(QList<Shadow> shadowList);
	void setFillsList(QList<Fills> fillsList);
	void setShape(QPainterPath shape);
	void setBlurRadius(qreal radius);

protected:
	void draw(QPainter *painter) override;
	void drawShadow(Shadow shadow, QPainter *p, const QPointF &pos, const QPixmap &px, bool isInnerShadow = false) const;
	void drawBlur(QPainter *p, const QPointF &pos, const QPixmap &px) const;
	void drawFills(Fills fills, QPainter *p) const;



private:
	qreal m_shadowRadius;
	qreal m_blurRadius;

	QList<Shadow> m_shadowList;
	QList<Fills> m_fillsList;
	QPainterPath m_shape;

};

#endif // ITEMEFFECTS_H
