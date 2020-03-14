/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

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

#include "pathprocessor.h"
#include "skia_includes.h"
#include "qt2skia.h"
#include "skia2qt.h"

#include <QDebug>

QPainterPath PathProcessor::combine(const QPainterPath &path1, const QPainterPath &path2, PathProcessor::Booleans boolOperator)
{
    return skia::qtPath( combine(
                             skia::skPath(path1),
                             skia::skPath(path2),
                             boolOperator)
                         );
}

SkPath PathProcessor::combine(const SkPath &path1, const SkPath &path2, PathProcessor::Booleans boolOperator)
{
    SkPath result;

    //    kDifference_SkPathOp,         //!< subtract the op path from the first path
    //    kIntersect_SkPathOp,          //!< intersect the two paths
    //    kUnion_SkPathOp,              //!< union (inclusive-or) the two paths
    //    kXOR_SkPathOp,                //!< exclusive-or the two paths
    //    kReverseDifference_SkPathOp,  //!< subtract the first path from the op path

    switch (boolOperator) {
    case Booleans::Subtract:
        Op(path1, path2, SkPathOp::kDifference_SkPathOp, &result);
        break;
    case Booleans::Intersect:
        Op(path1, path2, SkPathOp::kIntersect_SkPathOp, &result);
        break;
    case Booleans::InvertIntersect:
        Op(path1, path2, SkPathOp::kXOR_SkPathOp, &result);
        break;
    case Booleans::Unite:
    default:
        Op(path1, path2, SkPathOp::kUnion_SkPathOp, &result);
        break;
    }

    return simplify(result);
}


QPainterPath PathProcessor::normalOffset( const QPainterPath &path, qreal amount){

    //    QPainterPathStroker stroker;
    //    stroker.setJoinStyle(Qt::PenJoinStyle::MiterJoin);
    //    // Stroke width of PathStroker will be 50% of each side

    //    if(amount > 0){
    //        stroker.setWidth( amount );
    //        const QPainterPath stroked = stroker.createStroke( path );
    //        return combine(path, stroked, PathProcessor::Booleans::Unite);
    //    }else if(amount < 0){
    //        stroker.setWidth( -amount );
    //        const QPainterPath stroked = stroker.createStroke( path );
    //        return combine(path, stroked, PathProcessor::Booleans::Subtract);
    //    }else return path;


    return skia::qtPath( normalOffset( skia::skPath(path), amount) );


}

SkPath PathProcessor::normalOffset(const SkPath &path, qreal amount)
{
    SkPath target = path;

    QPen pen;
    pen.setJoinStyle(Qt::MiterJoin);


    if(amount > 0){
        pen.setWidthF(amount);
        target = combine(path, stroker(path, pen), PathProcessor::Booleans::Unite);
    }else if(amount < 0){
        pen.setWidthF(-amount);
        target = combine(path, stroker(path, pen), PathProcessor::Booleans::Subtract);
    }

    return target;
}

QPainterPath PathProcessor::stroker(const QPainterPath &path, QPen pen)
{
    //    QPainterPathStroker stroker(pen);
    //    return stroker.createStroke(path);

    return skia::qtPath( stroker( skia::skPath(path), pen) );
}

SkPath PathProcessor::stroker(const SkPath &path, QPen pen)
{
    SkPath target;

    SkPaint::Cap cap;
    SkPaint::Join join;

    switch(pen.capStyle()){
    default:
    case Qt::FlatCap:
        cap = SkPaint::Cap::kButt_Cap;
        break;
    case Qt::RoundCap:
        cap = SkPaint::Cap::kRound_Cap;
        break;
    case Qt::SquareCap:
        cap = SkPaint::Cap::kSquare_Cap;
        break;
    }

    switch(pen.joinStyle()){
    default:
    case Qt::MiterJoin:
        join = SkPaint::Join::kMiter_Join;
        break;
    case Qt::BevelJoin:
        join = SkPaint::Join::kBevel_Join;
        break;
    case Qt::RoundJoin:
        join = SkPaint::Join::kRound_Join;
        break;
    }


    QVector<qreal> pattern = pen.dashPattern();
    int pLenght = pattern.size();

    SkScalar intervals[pLenght];
    for(int i=0; i<pLenght; ++i){
        intervals[i] = SkFloatToScalar(pattern[i] * pen.widthF());
    }

    size_t count = sizeof(intervals) / sizeof(intervals[0]);

    SkPaint paint;
    paint.setPathEffect(SkDashPathEffect::Make(intervals, count, 0.0f));
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(pen.widthF());
    paint.setStrokeCap(cap);
    paint.setStrokeJoin(join);
    paint.setStrokeMiter(pen.miterLimit());
    paint.getFillPath(path, &target);

    return simplify(target);
}

QPainterPath PathProcessor::simplify(QPainterPath path)
{
    return skia::qtPath( simplify(skia::skPath(path)) );
}

SkPath PathProcessor::simplify(SkPath path)
{
    SkPath result;
    Simplify(path, &result);
    return result;
}

QPainterPath PathProcessor::map(QTransform transform, QPainterPath sourcePath)
{
    return skia::qtPath( map( skia::skMatrix(transform), skia::skPath(sourcePath) ) );
}

SkPath PathProcessor::map(SkMatrix matrix, SkPath sourcePath)
{
    SkPath path;
    sourcePath.transform(matrix, &path);
    return path;

}
