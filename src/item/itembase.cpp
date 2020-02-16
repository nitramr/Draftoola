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

#include <itembase.h>
#include <QDebug>
#include <path/pathhandler.h>
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

QT_BEGIN_NAMESPACE
// https://code.woboq.org/qt5/qtbase/src/widgets/effects/qpixmapfilter.cpp.html
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

ItemBase::ItemBase(const QRectF rect, QGraphicsItem *parent) : AbstractItemBase(rect, parent)
{
    m_strokePosition = Stroke::Inner;
    m_fillsList = QList<Fills>();
    m_strokeList = QList<Stroke>();
    m_shadowList = QList<Shadow>();
    m_innerShadowList = QList<Shadow>();
    m_hasFills = false;
    m_hasShadows = false;
    m_hasStrokes = false;
    m_hasInnerShadows = false;

    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    this->setFlag(QGraphicsItem::ItemContainsChildrenInShape, true);

//    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
//    blur->setBlurRadius(20);
//    setGraphicsEffect(blur);

}

//ItemBase::ItemBase(const ItemBase &other) : AbstractItemBase(other)
//{
//    m_id = other.m_id;
//    m_name = other.m_name;
//    m_strokePosition = other.m_strokePosition;
//    m_renderQuality = other.m_renderQuality;
//    m_shadowPath = other.m_shadowPath;
//    m_renderRect = other.m_renderRect;
//    m_fillsList = other.m_fillsList;
//    m_strokeList = other.m_strokeList;
//    m_shadowList = other.m_shadowList;
//    m_innerShadowList = other.m_innerShadowList;

//}

bool ItemBase::operator==(const ItemBase &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_name == other.m_name &&
            m_strokePosition == other.m_strokePosition &&
            m_renderQuality == other.m_renderQuality &&
            m_shadowPath == other.m_shadowPath &&
            m_renderRect == other.m_renderRect &&
            m_fillsList == other.m_fillsList &&
            m_strokeList == other.m_strokeList &&
            m_shadowList == other.m_shadowList &&
            m_innerShadowList == other.m_innerShadowList &&
            AbstractItemBase::operator==(other);
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

/**
 * @brief Returns level of details value. If highRenderQuality() = true it returns best level but results in slow rendering.
 * @return
 */
qreal ItemBase::lod()
{
    switch(renderQuality()){
    // m_lod = best render result but slow
    case RenderQuality::Quality:
        return m_lod;
        break;

        // 2.0 = mid render quality with good speed
    default:
    case RenderQuality::Balanced:
        return qMin(2.0, m_lod);
        break;

        // 1.0 = worst render result but fast
    case RenderQuality::Performance:
        return 1.0;
        break;
    }
}


QRectF ItemBase::renderRect() const
{
    return m_renderRect;
}

void ItemBase::clipsChildrenToShape(bool doClip)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, doClip);
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void ItemBase::addStroke(Stroke stroke)
{
    m_strokeList.append(stroke);
    m_hasStrokes = hasStrokes();
    calculateRenderRect();
    setInvalidateCache(true);
}

void ItemBase::updateStroke(Stroke stroke)
{
    for(int i=0; i < m_strokeList.count(); i++){
        Stroke m_property = m_strokeList.at(i);
        if(m_property.ID() == stroke.ID()){
            m_strokeList.replace(i,stroke);
            m_hasStrokes = hasStrokes();
            calculateRenderRect();
            setInvalidateCache(true);
            update();
            return;
        }
    }
}

void ItemBase::removeStroke(Stroke stroke)
{
    m_strokeList.removeOne(stroke);
    m_hasStrokes = hasStrokes();
    calculateRenderRect();
    setInvalidateCache(true);
    update();
}

Stroke ItemBase::stroke(int id) const
{
    id = qMin(m_strokeList.size()-1, qMax(0, id));
    return m_strokeList.at(id);
}


QList<Stroke> ItemBase::strokeList() const
{
    return m_strokeList;
}

bool ItemBase::hasStrokes() const
{
    if(m_strokeList.count() <= 0) return false;
    foreach(Stroke m_item, m_strokeList){
        if(m_item.isOn()){
            return true;
        }
    }
    return false;
}

void ItemBase::addFills(Fills fills)
{
    m_fillsList.append(fills);
    m_hasFills = hasFills();
    calculateRenderRect();
    setInvalidateCache(true);
}

void ItemBase::updateFills(Fills fills)
{
    for(int i=0; i < m_fillsList.count(); i++){
        Fills m_property = m_fillsList.at(i);
        if(m_property.ID() == fills.ID()){
            m_fillsList.replace(i,fills);
            m_hasFills = hasFills();
            calculateRenderRect();
            setInvalidateCache(true);
            update();
            return;
        }
    }
}

void ItemBase::removeFills(Fills fills)
{
    m_fillsList.removeOne(fills);
    m_hasFills = hasFills();
    calculateRenderRect();
    setInvalidateCache(true);
    update();
}

Fills ItemBase::fills(int id) const
{
    id = qMin(m_fillsList.size()-1, qMax(0, id));
    return m_fillsList.at(id);
}

QList<Fills> ItemBase::fillsList() const
{
    return m_fillsList;
}

bool ItemBase::hasFills() const
{
    if(m_fillsList.count() <= 0) return false;

    foreach(Fills m_item, m_fillsList){
        if(m_item.isOn()){
            return true;
        }
    }
    return false;
}

void ItemBase::addShadow(Shadow shadow)
{
    m_shadowList.append(shadow);
    m_hasShadows = hasShadows();
    calculateRenderRect();
    setInvalidateCache(true);
}

void ItemBase::updateShadow(Shadow shadow)
{
    for(int i=0; i < m_shadowList.count(); i++){
        Shadow m_property = m_shadowList.at(i);
        if(m_property.ID() == shadow.ID()){
            m_shadowList.replace(i,shadow);
            m_hasShadows = hasShadows();
            calculateRenderRect();
            setInvalidateCache(true);
            update();
            return;
        }
    }
}

void ItemBase::removeShadow(Shadow shadow)
{
    m_shadowList.removeOne(shadow);
    m_hasShadows = hasShadows();
    calculateRenderRect();
    setInvalidateCache(true);
    update();
}

Shadow ItemBase::shadow(int id) const
{
    id = qMin(m_shadowList.size()-1, qMax(0, id));
    return m_shadowList.at(id);
}

QList<Shadow> ItemBase::shadowList() const
{
    return m_shadowList;
}

bool ItemBase::hasShadows() const
{
    if(m_shadowList.count() <= 0) return false;

    foreach(Shadow m_item, m_shadowList){
        if(m_item.isOn()){
            return true;
        }
    }
    return false;
}

void ItemBase::addInnerShadow(Shadow shadow)
{
    m_innerShadowList.append(shadow);
    m_hasInnerShadows = hasInnerShadows();
    calculateRenderRect();
    setInvalidateCache(true);
}

void ItemBase::updateInnerShadow(Shadow shadow)
{
    for(int i=0; i < m_innerShadowList.count(); i++){
        Shadow m_property = m_innerShadowList.at(i);
        if(m_property.ID() == shadow.ID()){
            m_innerShadowList.replace(i,shadow);
            m_hasInnerShadows = hasInnerShadows();
            calculateRenderRect();
            setInvalidateCache(true);
            update();
            return;
        }
    }
}

void ItemBase::removeInnerShadow(Shadow shadow)
{
    m_innerShadowList.removeOne(shadow);
    m_hasInnerShadows = hasInnerShadows();
    calculateRenderRect();
    setInvalidateCache(true);
    update();
}

Shadow ItemBase::innerShadow(int id) const
{
    id = qMin(m_innerShadowList.size()-1, qMax(0, id));
    return m_innerShadowList.at(id);
}

QList<Shadow> ItemBase::innerShadowList() const
{
    return m_innerShadowList;
}

bool ItemBase::hasInnerShadows() const
{
    if(m_innerShadowList.count() <= 0) return false;

    foreach(Shadow m_item, m_innerShadowList){
        if(m_item.isOn()){
            return true;
        }
    }
    return false;
}


///
/// \brief Returns outlined shape of a rendered stroke
/// \param path
/// \param amount
/// \param pen
/// \return
///
QPainterPath ItemBase::scaleStroke(const QPainterPath &path, qreal amount, QPen pen) const
{
    QPainterPathStroker stroker(pen);
    //    stroker.setJoinStyle(Qt::PenJoinStyle::MiterJoin);
    //    stroker.setCurveThreshold(0.01); // BUG? Smaller values should be smooth the border

    // Stroke width of PathStroker will be 50% of each side

    if(amount > 0){
        stroker.setWidth( amount );
        const QPainterPath stroked = stroker.createStroke( path );
        return stroked ;
    }else if(amount < 0){
        stroker.setWidth( -amount );
        const QPainterPath stroked = stroker.createStroke( path );
        return stroked;
    }else return path;
}

void ItemBase::addItem(AbstractItemBase *item)
{
    item->setParentItem(this);
}

QRectF ItemBase::drawShadow(Shadow shadow, QPainter *painter)
{
    if(!shadow.isOn()) return QRectF();

    PathHandler pHandler;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, (renderQuality() == RenderQuality::Performance) ? false : true );
    painter->setCompositionMode(shadow.blendMode());


    // plain values
    qreal buffer = 0; // additional space around the bounding box
    qreal m_offsetX = shadow.offset().x();
    qreal m_offsetY = shadow.offset().y();
    qreal m_radiusShadow = shadow.radius();
    QColor m_color = shadow.color();

    // add spread
    QPainterPath mask = m_shadowPathList.value(shadow.ID());
    mask.setFillRule(Qt::FillRule::WindingFill);

    QRectF target(mask.boundingRect().adjusted(-m_radiusShadow - buffer,
                                               -m_radiusShadow - buffer,
                                               m_radiusShadow + buffer,
                                               m_radiusShadow + buffer
                                               ));
    target.translate(m_offsetX, m_offsetY);

    if(m_hasFills){
        QPainterPath clip;
        clip.addRect(target);
        clip = pHandler.combine(clip, shape(), PathHandler::Booleans::Subtract);
        painter->setClipPath(clip, Qt::ClipOperation::IntersectClip);
    }

    qreal _lod = lod();

    if(m_radiusShadow > 0){

        qreal m_width = (mask.boundingRect().width() + buffer * 2 + m_radiusShadow * 2) * _lod;
        qreal m_height = (mask.boundingRect().height() + buffer * 2 + m_radiusShadow * 2) * _lod;

        mask.translate(mask.boundingRect().left() * -1 + buffer + m_radiusShadow,
                       mask.boundingRect().top() * -1 +buffer + m_radiusShadow);

        // Blur shadow
        QImage tmp = blurShadow(mask,
                                QSize(qRound(m_width), qRound(m_height)),
                                m_radiusShadow,
                                _lod,
                                QPainter::CompositionMode_SourceIn,
                                m_color);


        // draw shadow
        painter->drawImage(target, tmp, QRectF(tmp.rect()));

    }else{
        mask.translate(m_offsetX,
                       m_offsetY);
        painter->setBrush(m_color);
        painter->drawPath(mask);
    }

    painter->restore();
    return target;

}

QRectF ItemBase::drawInnerShadow(Shadow shadow, QPainter *painter)
{
    if(!shadow.isOn() || rect().width() == 0 || rect().height() == 0) return QRectF();

    PathHandler pHandler;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, (renderQuality() == RenderQuality::Performance) ? false : true);
    painter->setCompositionMode(shadow.blendMode());
    painter->setClipPath(shape(), Qt::ClipOperation::IntersectClip);


    QRectF target(shape().boundingRect());

    // plain values
    qreal m_radiusShadow = shadow.radius();
    QColor m_color = shadow.color();


    // adjusted Shape
    QPainterPath mask = m_innerShadowPathList.value(shadow.ID());    
    mask.translate(shadow.offset().x(), shadow.offset().y());

    qreal _lod = lod();

    if(m_radiusShadow > 0){

        qreal m_width = shape().boundingRect().width() * _lod;
        qreal m_height = shape().boundingRect().height() * _lod;

        // adjust offset if shape top left point doesn't match rect top left point
        QPointF shapeOffset = mapToItem(this, shape().boundingRect().topLeft());
        mask.translate(-shapeOffset.x(), -shapeOffset.y());

        // Blur shadow
        QImage tmp = blurShadow(mask,
                                QSize(static_cast<int>(m_width), static_cast<int>(m_height)),
                                m_radiusShadow,
                                _lod,
                                QPainter::CompositionMode_SourceOut,
                                m_color);

        painter->drawImage(target, tmp, QRectF(tmp.rect()));

    }else{
        painter->setBrush(m_color);
        QPainterPath invMask = pHandler.combine(shape(), mask, PathHandler::Booleans::Subtract);
        painter->drawPath(invMask);
    }

    painter->restore();
    return target;

}

QRectF ItemBase::drawFills(Fills fills, QPainter *painter)
{
    if(!fills.isOn() || rect().width() == 0 || rect().height() == 0) return QRectF();

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, (renderQuality() == RenderQuality::Quality) ? true : false);
    painter->setCompositionMode(fills.blendMode());

    QRectF shapeRect = shape().boundingRect();    

    switch(fills.fillType()){
    case FillType::Color:{
        painter->setBrush(QBrush(fills.color()));
        painter->drawPath(shape());
        break;
    }
    case FillType::Pattern:{

        //        QMatrix m_matrix;
        //        m_matrix.scale(scaleFactor(), scaleFactor());

        //        QBrush brush(fills.color(),fills.style());
        //        brush.setMatrix(m_matrix.inverted());
        //        painter->setBrush(brush);
        //        painter->drawPath(shape());
        break;
    }
    case FillType::RadialGradient:{
        QRadialGradient rg(fills.gradient().radial(rect()));
        rg.setCenter(rect().center());
        painter->setOpacity(fills.opacity());
        painter->setBrush(QBrush(rg));
        painter->drawPath(shape());
        break;
    }
    case FillType::ConicalGradient:{
        QConicalGradient cg(fills.gradient().conical(rect()));
        cg.setCenter(rect().center());
        painter->setOpacity(fills.opacity());
        painter->setBrush(QBrush(cg));
        painter->drawPath(shape());
        break;
    }
    case FillType::LinearGradient:{
        painter->setOpacity(fills.opacity());
        painter->setBrush(QBrush( fills.gradient().linear( QLineF(QPointF(), QPointF(0,rect().bottom())) ) ));
        painter->drawPath(shape());
        break;
    }
    case FillType::Image:{
        QPixmap texture = fills.pixmap();
        if(!texture.isNull())
        {

            QRect imgRect;
            qreal xratio = texture.width() / shapeRect.width();
            qreal yratio = texture.height() / shapeRect.height();
            qreal xOffset = 0;
            qreal yOffset = 0;

            // Respect the aspect ratio mode.
            switch (fills.fillMode()) {
            case Fills::Fill:
                xratio = yratio = qMin(xratio, yratio);
                xOffset = (texture.width() - shapeRect.width() * xratio) / 2;
                yOffset = (texture.height() - shapeRect.height() * yratio) / 2;

                break;
            case Fills::Fit:
                xratio = yratio = qMax(xratio, yratio);

                break;
            case Fills::Stretch:
                // nothing to do
                break;
            case Fills::Tile:
                painter->drawTiledPixmap(shapeRect.toRect(), texture);
                painter->restore();

                return shapeRect;
            }

            imgRect = QRect(static_cast<int>(xOffset),
                            static_cast<int>(yOffset),
                            static_cast<int>(shapeRect.width() * xratio),
                            static_cast<int>(shapeRect.height() * yratio ));

            painter->setOpacity(fills.opacity());
            painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
            painter->setClipPath(shape(), Qt::ClipOperation::IntersectClip);
            painter->drawPixmap(shapeRect, texture, imgRect);

        }

        break;
    }
    }

    painter->restore();

    return shapeRect;
}

QRectF ItemBase::drawStrokes(Stroke stroke, QPainter *painter)
{

    if(!stroke.isOn() || stroke.widthF() <= 0) return QRectF();

    PathHandler pHandler;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF boundingBox = shape().boundingRect();
    qreal width = stroke.widthF();
    qreal offset = width/2;

    QPainterPath pathStroke = shape();

    switch(stroke.strokePosition()){
    case Stroke::Inner:
        offset = 0;
        stroke.setWidthF(width * 2);
        painter->setClipPath(shape(), Qt::ClipOperation::IntersectClip);
        break;
    case Stroke::Outer:{
        offset = width;
        stroke.setWidthF(width * 2);
        QPainterPath tmpMask;
        tmpMask.addRect(boundingBox.adjusted(-offset,-offset,offset,offset));
        painter->setClipPath(tmpMask.subtracted(shape()), Qt::ClipOperation::IntersectClip);
        break;
    }
    case Stroke::Center:
        break;
    }

    painter->setPen(stroke.pen());
    painter->drawPath(pathStroke);
    painter->restore();

    return boundingBox.adjusted(-offset,-offset,offset,offset);
}


QRectF ItemBase::drawBlur(qreal radius, QPainter* painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF boundingBox = shape().boundingRect();

    // Add Blur Logic


    painter->restore();

    return boundingBox;
}

QPainterPath ItemBase::strokeShape() const
{
    QPainterPath strokeShape;

    if(m_hasStrokes){
        PathHandler pHandler;
        QPainterPath pathMask = shape();

        foreach(Stroke stroke, strokeList()) {
            if(stroke.isOn()){
                qreal width = stroke.widthF();
                switch(stroke.strokePosition()){
                case Stroke::Inner:
                    pathMask = pHandler.combine(scaleStroke(shape(), width*2, stroke.pen()), shape(), PathHandler::Booleans::Intersect);
                    break;
                case Stroke::Outer:{
                    pathMask = pHandler.combine(scaleStroke(shape(), width*2, stroke.pen()), shape(), PathHandler::Booleans::Subtract);
                    break;
                }
                case Stroke::Center:
                    pathMask = scaleStroke(shape(), width, stroke.pen());
                    break;
                }

                strokeShape = pHandler.combine(strokeShape, pathMask, PathHandler::Booleans::Unite);
            }
        }
    }

    return strokeShape;
}


// https://code.woboq.org/qt5/qtbase/src/widgets/effects/qpixmapfilter.cpp.html
// void QPixmapDropShadowFilter::draw(QPainter *p, const QPointF &pos, const QPixmap &px, const QRectF &src) const

QImage ItemBase::blurShadow(QPainterPath shape, QSize size, qreal radius, qreal lod, QPainter::CompositionMode compositionMode, QColor color) const
{
    // Draw Shadow Pixmap
    QImage tmp(size, QImage::Format_ARGB32_Premultiplied);
    tmp.fill(0);

    QPainter pxPainter(&tmp);
    pxPainter.scale(lod,lod);
    pxPainter.setRenderHint(QPainter::Antialiasing, true);
    pxPainter.fillPath(shape, Qt::black);
    pxPainter.end();

    // blur the alpha channel
    QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.fill(0);
    QPainter blurPainter(&blurred);

    qt_blurImage(&blurPainter, tmp, radius * lod, m_doRender, true);

    tmp = blurred;

    // tint Shadow
    pxPainter.begin(&tmp);
    pxPainter.setCompositionMode(compositionMode);
    pxPainter.fillRect(blurred.rect(), QBrush(color));
    pxPainter.end();

    return tmp;
}


void ItemBase::calculateRenderRect()
{
    m_shadowPath = QPainterPath();

 //   if(m_hasFills){
        m_shadowPath = shape();
 //   }

    if(m_hasStrokes){
        m_shadowPath.addPath(strokeShape());
    }

    // Calculate inner shadow paths
    calculateInnerShadowPaths();

    // Calculate drop shadow paths
    QRectF tmpRect = calculateShadowPaths();
    m_renderRect = m_boundingRect = (tmpRect.isEmpty()) ? shape().boundingRect() : tmpRect;


}


QRectF ItemBase::calculateShadowPaths()
{
    m_shadowPathList.clear();
    PathHandler pHandler;
    QRectF bound = m_shadowPath.boundingRect();

    foreach(Shadow shadow, m_shadowList){
        if(shadow.isOn()){
            QPainterPath mask = pHandler.scale(m_shadowPath, shadow.spread()*2);
            m_shadowPathList.insert(shadow.ID(),mask);

            qreal radius = shadow.radius();
            QRectF shadowRect = mask.boundingRect();
            shadowRect.translate(shadow.offset());
            shadowRect.adjust(-radius, -radius, radius, radius);
            bound = bound.united(shadowRect);
        }
    }

    return bound;
}

void ItemBase::calculateInnerShadowPaths()
{
    m_innerShadowPathList.clear();
    PathHandler pHandler;   

    foreach(Shadow shadow, m_innerShadowList){
        if(shadow.isOn()){
            QPainterPath mask = pHandler.scale(shape(), -shadow.radius() - shadow.spread());
            m_innerShadowPathList.insert(shadow.ID(),mask);
        }
    }
}


void ItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    Q_UNUSED(widget);

    if (rect().width() <= 0 || rect().height() <= 0) return;

    m_lod = option->levelOfDetailFromTransform( painter->transform());

    // Drop Shadow
    if(m_hasShadows){
        foreach(Shadow shadow, this->shadowList())
            drawShadow(shadow, painter);
    }

    // Draw Fills
    if(m_hasFills){
        foreach(Fills fills,this->fillsList())
            drawFills(fills, painter);
    }

    // Draw InnerShadows
    if(m_hasInnerShadows){
        foreach(Shadow shadow, this->innerShadowList())
            drawInnerShadow(shadow, painter);
    }

    // Draw Strokes
    if(m_hasStrokes){
        foreach(Stroke stroke, this->strokeList())
            drawStrokes(stroke, painter);
        }
}

void ItemBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    if(shape().contains(mapFromScene(event->scenePos())) ){
        this->setSelected(true);
    }else{
        this->setSelected(false);
    }
}

void ItemBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(shape().contains(mapFromScene(event->scenePos())) ){
        this->setSelected(true);
    }else{
        this->setSelected(false);
    }

}
