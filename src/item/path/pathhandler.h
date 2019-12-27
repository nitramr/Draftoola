#ifndef PATHHANDLER_H
#define PATHHANDLER_H

#include <QPainterPath>

class PathHandler
{
public:
    PathHandler();

    enum class Booleans {
        Unite = 0,
        Subtract = 1,
        Intersect = 2,
        InvertIntersect = 3
    };

    static QPainterPath combine(const QPainterPath &path1, const QPainterPath &path2, Booleans boolOperator = Booleans::Unite);
    QPainterPath scale( const QPainterPath & path, qreal amount) const;
    QPainterPath simplify(QPainterPath path) const;

};

#endif // PATHHANDLER_H
