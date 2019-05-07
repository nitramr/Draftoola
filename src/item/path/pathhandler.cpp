#include "pathhandler.h"

#include <QDebug>


PathHandler::PathHandler()
{

}

QPainterPath PathHandler::combine(const QPainterPath &path1, const QPainterPath &path2, PathHandler::Booleans boolOperator)
{
    QPainterPath combinedPath;

    // TODO: add operations which combine bezier paths into a new bezier path instead of polygons like the default Qt operations.

    switch (boolOperator) {
    case Booleans::Subtract:
        combinedPath = path1.subtracted(path2);
        break;
    case Booleans::Intersect:
        combinedPath = path1.intersected(path2);
        break;
    case Booleans::InvertIntersect:
        combinedPath = path1.subtractedInverted(path2);
        break;
    case Booleans::Unite:
    default:
        combinedPath = path1.united(path2);
        break;
    }

    return combinedPath;
}


QPainterPath PathHandler::scale( const QPainterPath & path, qreal amount) const {
    QPainterPathStroker stroker;
    stroker.setJoinStyle(Qt::PenJoinStyle::MiterJoin);
    // Stroke width of PathStroker will be 50% of each side

        if(amount > 0){
            stroker.setWidth( amount );
            const QPainterPath stroked = stroker.createStroke( path );
            return combine(path, stroked, PathHandler::Booleans::Unite);
        }else if(amount < 0){
            stroker.setWidth( -amount );
            const QPainterPath stroked = stroker.createStroke( path );
            return combine(path, stroked, PathHandler::Booleans::Subtract);
        }else return path;

}

QPainterPath PathHandler::simplify(QPainterPath path) const
{

    return path.simplified();

    // https://github.com/radekp/qt/blob/master/src/gui/painting/qbezier.cpp


//    QList<QPointF> m_points;
//    int last = 0;

//    for (int i = 0; i < path.elementCount(); ++i) {

//        int current = m_points.size();

//        QPointF currentPoint;
//        if (path.elementAt(i).type == QPainterPath::CurveToElement)
//        currentPoint = path.elementAt(i+2); // go to real point
//        else
//        currentPoint = path.elementAt(i);

//        switch (path.elementAt(i).type) {
//        case QPainterPath::MoveToElement:
//            break;
//        case QPainterPath::LineToElement:
//            break;
//        case QPainterPath::CurveToElement:
//            //QBezier bezier = QBezier::fromPoints(m_points.at(last), path.elementAt(i), path.elementAt(i+1), path.elementAt(i+2));
//            break;
//        default:
//            break;
//        }

//    }

//    return path;
}
