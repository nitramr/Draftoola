#include "itempolygon.h"
#include <QtGlobal>
#include <QtMath>

ItemPolygon::ItemPolygon(QGraphicsItem *parent) : ItemPolygon(0,0,300,350, 10, parent){}
ItemPolygon::ItemPolygon(qreal x, qreal y, qreal width, qreal height, int sides, QGraphicsItem *parent) : ItemPolygon(QRectF(x,y,width,height), sides, parent){}
ItemPolygon::ItemPolygon(qreal width, qreal height, int sides, QGraphicsItem *parent) : ItemPolygon(QRectF(0,0,width,height), sides, parent){}
ItemPolygon::ItemPolygon(QRectF rect, int sides, QGraphicsItem *parent) : ItemBase(rect, parent){

    m_sides = sides;
    m_innerLength = 0.5;
    this->setRect(rect);
    this->setName(tr("Rect"));
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemPolygon::setSides(int count)
{
    m_sides = count;
    setRect(rect());
}

int ItemPolygon::sides() const
{
    return m_sides;
}

void ItemPolygon::setInnerLength(qreal length)
{
    m_innerLength = qMin(qMax(length, 0.0), 1.0);
    setRect(rect());
}

qreal ItemPolygon::innerLength() const
{
    return m_innerLength;
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
    int points = m_sides;
    int angle = -90;

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

        qreal length = (i % 2) ? line.length() * m_innerLength: line.length();
        line.setLength(length);

        polygon.lineTo( line.p2() );

        angle +=360 / points;
    }

    polygon.closeSubpath();
    return polygon;
}
