#ifndef ITEMSTAR_H
#define ITEMSTAR_H

#include <itembase.h>

class ItemPolygon : public ItemBase
{
public:
    ItemPolygon(qreal x, qreal y, qreal width, qreal height, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(qreal width, qreal height, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(QRectF rect, int sides = 10, bool useInnerRadius = false, QGraphicsItem * parent = nullptr);
    ItemPolygon(QGraphicsItem * parent = nullptr);
    ItemPolygon(const ItemPolygon &other);


    // operator
    bool operator==( const ItemPolygon & other ) const;
    inline bool operator!=(const ItemPolygon &itemBase) const;


    // Properties
    int type() const override { return Type::Polygon; }
    void setSides(int count);
    int sides() const;
    void setInnerRadius(qreal length);
    qreal innerRadius() const;
    void setUseInnerRadius(bool allow);
    bool useInnerRadius();

    void setRect(QRectF rect) override;
    virtual QPainterPath shapeScaled(QRectF frame) const;

private:
    int m_sides;
    qreal m_innerRadius;
    bool m_useInnerRadius;

};

#endif // ITEMSTAR_H
