#include <itempolygon.h>
#include <QtGlobal>
#include <QtMath>

ItemPolygon::ItemPolygon(QGraphicsItem *parent) : ItemPolygon(0,0,80,80, 10, parent){}
ItemPolygon::ItemPolygon(qreal x, qreal y, qreal width, qreal height, int sides, bool useInnerRadius, QGraphicsItem *parent) : ItemPolygon(QRectF(x,y,width,height), sides, useInnerRadius, parent){}
ItemPolygon::ItemPolygon(qreal width, qreal height, int sides, bool useInnerRadius, QGraphicsItem *parent) : ItemPolygon(QRectF(0,0,width,height), sides, useInnerRadius, parent){}
ItemPolygon::ItemPolygon(QRectF rect, int sides, bool useInnerRadius, QGraphicsItem *parent) : ItemBase(rect, parent){

    m_innerRadius = 0.5;
    m_useInnerRadius = useInnerRadius;
    m_sides = qMin(qMax(sides, 3), (m_useInnerRadius) ? 50 : 10);
    this->setRect(rect);
    this->setName(tr("Polygon"));
}


ItemPolygon::ItemPolygon(const ItemPolygon &other) : ItemBase(other)
{
    m_sides = other.m_sides;
    m_innerRadius = other.m_innerRadius;
    m_useInnerRadius = other.m_useInnerRadius;
}


bool ItemPolygon::operator==(const ItemPolygon &other) const
{
    if(this == &other) return true;

    return m_sides == other.m_sides &&
            m_innerRadius == other.m_innerRadius &&
            m_useInnerRadius == other.m_useInnerRadius &&
            ItemBase::operator==(other);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemPolygon::setSides(int count)
{
    m_sides = qMin(qMax(count, 3), (m_useInnerRadius) ? 50 : 10);
    setRect(rect());
}

int ItemPolygon::sides() const
{
    return m_sides;
}

void ItemPolygon::setInnerRadius(qreal length)
{
    m_innerRadius = qMin(qMax(length, 0.0), 1.0);
    setRect(rect());
}

qreal ItemPolygon::innerRadius() const
{
    return m_innerRadius;
}

void ItemPolygon::setUseInnerRadius(bool allow)
{
    m_useInnerRadius = allow;
}

bool ItemPolygon::useInnerRadius()
{
    return m_useInnerRadius;
}

void ItemPolygon::setRect(QRectF rect)
{
    switch(frameType()){
    case AbstractItemBase::FixedWidth:
        rect.setWidth(this->rect().width());
        break;
    case AbstractItemBase::FixedHeight:
        rect.setHeight(this->rect().height());
        break;
    case AbstractItemBase::FixedSize:
        rect = this->rect();
        break;
    case AbstractItemBase::Free:
        break;
    }

    ItemBase::setShape(shapeScaled(rect));
    m_rect = rect;
}

QPainterPath ItemPolygon::shapeScaled(QRectF frame) const
{
    int points = (m_useInnerRadius) ? sides() *2 : sides();
    qreal angle = -90.0;

    QPointF center = frame.center();
    QPointF start(center.x(), frame.top());

    QPainterPath polygon(start);

    for (int i=0; i < points; i++){

        QPointF ellipsePoint(
                    center.x() + frame.width()/2 * qCos(angle * M_PI/180.0),
                    center.y() + frame.height()/2 * qSin(angle * M_PI/180.0)
                    );


        QLineF line;
        line.setP1(center);
        line.setP2(ellipsePoint);

        qreal length = (i % 2 && m_useInnerRadius) ? line.length() * innerRadius(): line.length();
        line.setLength(length);

        polygon.lineTo( line.p2() );

        angle +=360.0 / points;
    }

    polygon.closeSubpath();
    return polygon;
}
