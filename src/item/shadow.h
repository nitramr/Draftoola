#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "abstractitemproperty.h"

class Shadow : public AbstractItemProperty
{
//   Q_GADGET
public:
    // Constructor
    Shadow();
    Shadow(QString name, QColor color= QColor(0,0,0,128), qreal radius = 4, QPointF offset = QPointF(0,2), qreal spread = 0);
    Shadow(const Shadow &other);
    ~Shadow(){}

    bool operator==( const Shadow & other ) const;
    inline bool operator!=(const Shadow &shadow) const { return !(operator==(shadow)); }

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
Q_DECLARE_METATYPE(Shadow)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Shadow &shadow);
#endif

#endif // SHADOW_H
