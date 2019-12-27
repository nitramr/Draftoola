#include "roundedpolygon.h"
#include "math.h"

float RoundedPolygon::GetDistance(QPointF pt1, QPointF pt2) const
{
    float fD = (pt1.x() - pt2.x())*(pt1.x() - pt2.x()) +
         (pt1.y() - pt2.y()) * (pt1.y() - pt2.y());
    return sqrtf(fD);
}

QPointF RoundedPolygon::GetLineStart(int i) const
{
    QPointF pt;
    QPointF pt1 = at(i);
    QPointF pt2 = at((i+1) % count());
    float fRat = m_iRadius / GetDistance(pt1, pt2);
    if (fRat > 0.5f)
     fRat = 0.5f;

    pt.setX((1.0f-fRat)*pt1.x() + fRat*pt2.x());
    pt.setY((1.0f-fRat)*pt1.y() + fRat*pt2.y());
    return pt;
}

QPointF RoundedPolygon::GetLineEnd(int i) const
{
    QPointF pt;
    QPointF pt1 = at(i);
    QPointF pt2 = at((i+1) % count());
    float fRat = m_iRadius / GetDistance(pt1, pt2);
    if (fRat > 0.5f)
     fRat = 0.5f;
    pt.setX(fRat*pt1.x() + (1.0f - fRat)*pt2.x());
    pt.setY(fRat*pt1.y() + (1.0f - fRat)*pt2.y());
    return pt;
}

const QPainterPath& RoundedPolygon::GetPath()
{
    m_path = QPainterPath();

    if (count() < 3) {
     //qWarning() << "Polygon should have at least 3 points!";
     return m_path;
    }

    QPointF pt1;
    QPointF pt2;
    for (int i = 0; i < count(); i++) {
     pt1 = GetLineStart(i);

     if (i == 0)
         m_path.moveTo(pt1);
     else
         m_path.quadTo(at(i), pt1);

     pt2 = GetLineEnd(i);
     m_path.lineTo(pt2);
    }

    // close the last corner
    pt1 = GetLineStart(0);
    m_path.quadTo(at(0), pt1);

    return m_path;
}
