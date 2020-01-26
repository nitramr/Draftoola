/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

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
        combinedPath = path2.subtracted(path1);
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
