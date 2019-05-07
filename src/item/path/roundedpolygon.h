#ifndef ROUNDEDPOLYGON_H
#define ROUNDEDPOLYGON_H

#include <QPainterPath>

class RoundedPolygon : public QPolygonF
{
public:
    RoundedPolygon()
    {    SetRadius(10); }

    void SetRadius(unsigned int iRadius)
    {    m_iRadius = iRadius; }

    const QPainterPath& GetPath();

private:
    QPointF GetLineStart(int i) const;
    QPointF GetLineEnd(int i) const;
    float GetDistance(QPointF pt1, QPointF pt2) const;
private:
    QPainterPath m_path;
    unsigned int m_iRadius;
};

#endif // ROUNDEDPOLYGON_H
