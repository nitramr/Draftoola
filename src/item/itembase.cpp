#include "itembase.h"
#include <QDebug>
//#include <QGraphicsScene>
//#include <QPainter>
//#include <QtWidgets>
#include "path/pathhandler.h"
//#include <QGraphicsEffect>

QT_BEGIN_NAMESPACE
// https://code.woboq.org/qt5/qtbase/src/widgets/effects/qpixmapfilter.cpp.html
extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

ItemBase::ItemBase(const QRectF rect, QGraphicsItem *parent) : AbstractItemBase(rect, parent)
{
    m_strokePosition = StrokePosition::Inner;
    m_fillsList = QList<Fills>();
    m_strokeList = QList<Stroke>();
    m_shadowList = QList<Shadow>();
    m_innerShadowList = QList<Shadow>();
    m_invaliateCache = false;
    m_geometryHasChanged = true;
    m_contentHasChanged = true;
    m_cache = QPixmapCache();
    //    m_cache.setCacheLimit(51200); // 50MB

//    qShadow = new QGraphicsDropShadowEffect();
//    qShadow->setBlurRadius(10);
//    qShadow->setXOffset(2);

    //       setGraphicsEffect(qShadow);

    //        QGraphicsBlurEffect * blurEffect = new QGraphicsBlurEffect();
    //        blurEffect->setBlurRadius(1);
    //        setGraphicsEffect(blurEffect);

    //    QGraphicsColorizeEffect *eColor = new QGraphicsColorizeEffect();
    //    eColor->setColor(QColor(255,0,0));
    //    setGraphicsEffect(eColor);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemBase::addStroke(Stroke stroke)
{
    m_strokeList.append(stroke);
    setInvalidateCache(true);
}

Stroke ItemBase::stroke(int id) const
{
    id = qMin(m_strokeList.size()-1, qMax(0, id));
    return m_strokeList.at(id);
}

void ItemBase::updateStroke(Stroke stroke)
{
    for(int i=0; i < m_strokeList.count(); i++){
        Stroke m_property = m_strokeList.at(i);
        if(m_property.ID() == stroke.ID()){
            m_strokeList.replace(i,stroke);
            setInvalidateCache(true);
            update();
            return;
        }
    }
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
    setInvalidateCache(true);
}

Fills ItemBase::fills(int id) const
{
    id = qMin(m_fillsList.size()-1, qMax(0, id));
    return m_fillsList.at(id);
}

void ItemBase::updateFills(Fills fills)
{
    for(int i=0; i < m_fillsList.count(); i++){
        Fills m_property = m_fillsList.at(i);
        if(m_property.ID() == fills.ID()){
            m_fillsList.replace(i,fills);
            setInvalidateCache(true);
            update();
            return;
        }
    }
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
    setInvalidateCache(true);
}

Shadow ItemBase::shadow(int id) const
{
    id = qMin(m_shadowList.size()-1, qMax(0, id));
    return m_shadowList.at(id);
}

void ItemBase::updateShadow(Shadow shadow)
{
    for(int i=0; i < m_shadowList.count(); i++){
        Shadow m_property = m_shadowList.at(i);
        if(m_property.ID() == shadow.ID()){
            m_shadowList.replace(i,shadow);
            setInvalidateCache(true);
            update();
            return;
        }
    }
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
    setInvalidateCache(true);
}

Shadow ItemBase::innerShadow(int id) const
{
    id = qMin(m_innerShadowList.size()-1, qMax(0, id));
    return m_innerShadowList.at(id);
}

void ItemBase::updateInnerShadow(Shadow shadow)
{
    for(int i=0; i < m_innerShadowList.count(); i++){
        Shadow m_property = m_innerShadowList.at(i);
        if(m_property.ID() == shadow.ID()){
            m_innerShadowList.replace(i,shadow);
            setInvalidateCache(true);
            update();
            return;
        }
    }
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


/**
 * @brief Returns level of details value. If highRenderQuality() = true it returns best level but results in slow rendering.
 * @return
 */
qreal ItemBase::lod() const
{    
    qreal m_lod = scaleFactor();

    if(highRenderQuality()) return m_lod;

    if(m_lod > 2){
        // scaleFactor = best render result but slow
        // 1 = worst render result but fast
        // returns amount of pixels within 1 pixel
        return 2;
    }else return m_lod;
}


void ItemBase::setShape(QPainterPath itemShape)
{
    m_shape = itemShape;
    m_rect = m_shape.boundingRect().normalized();
    setInvalidateCache(true);
    this->setTransformOriginPoint(m_rect.center());
    m_geometryHasChanged = true;
    update();
}

QRectF ItemBase::renderRect() const
{
    return m_boundingRect;
}


void ItemBase::setShadowMapStroke(const QPainterPath &shape)
{
    m_shadowMapStroke = shape;
}

QPainterPath ItemBase::shadowMapStroke() const
{
    return m_shadowMapStroke;
}

void ItemBase::setShadowMapFill(const QPainterPath &shape)
{
    m_shadowMapFill = shape;
}

QPainterPath ItemBase::shadowMapFill() const
{
    return m_shadowMapFill;
}

void ItemBase::setGeometryHasChanged(bool hasChanged)
{
    m_geometryHasChanged = hasChanged;
}

bool ItemBase::geometryHasChanged() const
{
    return m_geometryHasChanged;
}

void ItemBase::setContentHasChanged(bool hasChanged)
{
    m_contentHasChanged = hasChanged;
}

bool ItemBase::contentHasChanged() const
{
    return m_contentHasChanged;
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

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
    m_children.append(item);
}

QRectF ItemBase::drawShadow(Shadow shadow, QPainter *painter)
{
    if(!shadow.isOn()) return QRectF();

    PathHandler pHandler;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, highRenderQuality());
    painter->setCompositionMode(shadow.blendMode());


    qreal m_lod = lod();

    // plain values
    qreal buffer = 0; // additional space around the bounding box
    qreal m_offsetX = shadow.offset().x();
    qreal m_offsetY = shadow.offset().y();
    qreal m_spread = shadow.spread();
    qreal m_radiusShadow = shadow.radius();
    QColor m_color = shadow.color();

    // unite stroke and fill shape to shadow mask
    QPainterPath shadowMap = pHandler.combine(shadowMapFill(),shadowMapStroke());

    // add spread
    QPainterPath mask = pHandler.scale(shadowMap, m_spread*2);
    mask.setFillRule(Qt::FillRule::WindingFill);

    QRectF target(mask.boundingRect().adjusted(-m_radiusShadow - buffer,
                                               -m_radiusShadow - buffer,
                                               m_radiusShadow + buffer,
                                               m_radiusShadow + buffer
                                               ));
    target.translate(m_offsetX, m_offsetY);

    if(hasFills()){
        QPainterPath clip;
        clip.addRect(target);
        clip = pHandler.combine(clip, shape(), PathHandler::Booleans::Subtract);
        painter->setClipPath(clip, Qt::ClipOperation::IntersectClip);
    }

    if(m_radiusShadow > 0){

        qreal m_width = (mask.boundingRect().width() + buffer * 2 + m_radiusShadow * 2) * m_lod;
        qreal m_height = (mask.boundingRect().height() + buffer * 2 + m_radiusShadow * 2) * m_lod;

        mask.translate(mask.boundingRect().left() * -1 + buffer + m_radiusShadow,
                       mask.boundingRect().top() * -1 +buffer + m_radiusShadow);

        // Blur shadow
        QImage tmp = blurShadow(mask,
                                QSize(qRound(m_width), qRound(m_height)),
                                m_radiusShadow,
                                m_lod,
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
    if(!shadow.isOn()) return QRectF();

    PathHandler pHandler;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, highRenderQuality());
    painter->setCompositionMode(shadow.blendMode());
    painter->setClipPath(shape(), Qt::ClipOperation::IntersectClip);

    qreal m_lod = lod();

    QRectF target(shape().boundingRect());

    // plain values
    qreal m_radiusShadow = shadow.radius() * 2;
    qreal m_spread = shadow.spread();
    QColor m_color = shadow.color();

    // adjusted Shape
    QPainterPath mask = pHandler.scale(shape(), -m_radiusShadow / 2 - m_spread);
    mask.translate(shadow.offset().x(), shadow.offset().y());


    if(m_radiusShadow > 0){

        qreal m_width = shape().boundingRect().width() * m_lod;
        qreal m_height = shape().boundingRect().height() * m_lod;

        // Blur shadow
        QImage tmp = blurShadow(mask,
                                QSize(static_cast<int>(m_width), static_cast<int>(m_height)),
                                m_radiusShadow,
                                m_lod,
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
    if(!fills.isOn()) return QRectF();

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, highRenderQuality());

    QRectF shapeRect = shape().boundingRect();

    painter->setOpacity(fills.opacity()/100.0);
    painter->setCompositionMode(fills.blendMode());

    switch(fills.fillType()){
    case FillType::Color:{
        painter->setBrush(QBrush(fills.color()));
        painter->drawPath(shape());
        break;
    }
    case FillType::Pattern:{

        QMatrix m_matrix;
        m_matrix.scale(scaleFactor(), scaleFactor());

        QBrush brush(fills.color(),fills.style());
        brush.setMatrix(m_matrix.inverted());
        painter->setBrush(brush);
        painter->drawPath(shape());
        break;
    }
    case FillType::Gradient:{

        QGradient gradient(fills.gradient());

        painter->setBrush(QBrush(gradient));
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
            case FillMode::Fill:
                xratio = yratio = qMin(xratio, yratio);
                xOffset = (texture.width() - shapeRect.width() * xratio) / 2;
                yOffset = (texture.height() - shapeRect.height() * yratio) / 2;

                break;
            case FillMode::Fit:
                xratio = yratio = qMax(xratio, yratio);

                break;
            case FillMode::Stretch:
                // nothing to do
                break;
            case FillMode::Tile:
                painter->drawTiledPixmap(shapeRect.toRect(), texture);
                painter->restore();

                return shapeRect;
            }

            imgRect = QRect(static_cast<int>(xOffset),
                            static_cast<int>(yOffset),
                            static_cast<int>(shapeRect.width() * xratio),
                            static_cast<int>(shapeRect.height() * yratio ));

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
    case StrokePosition::Inner:
        offset = 0;
        stroke.setWidthF(width * 2);
        painter->setClipPath(shape(), Qt::ClipOperation::IntersectClip);
        break;
    case StrokePosition::Outer:{
        offset = width;
        stroke.setWidthF(width * 2);
        QPainterPath tmpMask;
        tmpMask.addRect(boundingBox.adjusted(-offset,-offset,offset,offset));
        painter->setClipPath(tmpMask.subtracted(shape()), Qt::ClipOperation::IntersectClip);
        break;
    }
    case StrokePosition::Center:
        break;
    }

    painter->setPen(stroke);
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

    if(hasStrokes()){
        PathHandler pHandler;
        QPainterPath pathMask = shape();

        foreach(Stroke stroke, strokeList()) {
            qreal width = stroke.widthF();
            switch(stroke.strokePosition()){
            case StrokePosition::Inner:
                pathMask = pHandler.combine(scaleStroke(shape(), width*2, stroke), shape(), PathHandler::Booleans::Intersect);
                break;
            case StrokePosition::Outer:{
                pathMask = pHandler.combine(scaleStroke(shape(), width*2, stroke), shape(), PathHandler::Booleans::Subtract);
                break;
            }
            case StrokePosition::Center:
                pathMask = scaleStroke(shape(), width, stroke);
                break;
            }

            strokeShape = pHandler.combine(strokeShape, pathMask, PathHandler::Booleans::Unite);
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
    pxPainter.setBrush(QBrush(Qt::black));
    pxPainter.setPen(Qt::NoPen);
    pxPainter.drawPath(shape);
    pxPainter.end();

    // blur the alpha channel
    QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.fill(0);
    QPainter blurPainter(&blurred);
    qt_blurImage(&blurPainter, tmp, radius * lod, false, true);
    blurPainter.end();
    tmp = blurred;

    // tint Shadow
    pxPainter.begin(&tmp);
    pxPainter.setCompositionMode(compositionMode);
    pxPainter.fillRect(blurred.rect(), QBrush(color));
    pxPainter.end();

    return tmp;

}


/**
 * @brief Calculates bounding rectangle of all used shadows
 * @param shape
 * @return
 */
QRectF ItemBase::ShadowBound(QPainterPath shape) const
{
    QRectF bound = shape.boundingRect();

    foreach(Shadow shadow, shadowList()) {
        qreal radius = shadow.radius();
        qreal spread = shadow.spread();
        QPointF offset = shadow.offset();

        QRectF shadowRect = shape.boundingRect();
        shadowRect.translate(offset);
        shadowRect.adjust(-radius - spread,
                          -radius - spread,
                          radius + spread,
                          radius + spread
                          );
        bound = bound.united(shadowRect);
    }

    return bound;
}

void ItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    Q_UNUSED(widget);

    if (rect().width() <= 0 || rect().height() <= 0)
        return;

    qreal multiplier = scaleFactor(); //option->levelOfDetailFromTransform( painter->transform());

    // reset bounding box to minimum shape


//    QPixmap cache(qRound(rect().width() * m_scale), qRound(rect().height() * m_scale));
//    cache.fill(Qt::transparent);

//    QPainter cachePainter(&cache);
//    painter->scale(m_scale,m_scale);

//    setHighRenderQuality(true);
    render(painter, multiplier );

//    painter->drawPixmap(rect(),cache, cache.rect());




//    QImage image(QSize(qRound(boundingRect().width()*multiplier),qRound(boundingRect().height()*multiplier) ), QImage::Format_ARGB32_Premultiplied);
//            image.fill(Qt::transparent);

//            QPainter painter2(&image);
//            painter2.scale(multiplier,multiplier);
//            painter2.translate(boundingRect().topLeft().x() * -1, boundingRect().topLeft().y() * -1);
//            //painter.setRenderHint(QPainter::HighQualityAntialiasing);
//            setHighRenderQuality(true);
//            render(&painter2);
//            setHighRenderQuality(false);
//            painter2.end();

//            image.save("file_name_"+ QString::number(multiplier) + ".png");





    // BoundingBox
//    painter->save();
//    QPen pen = QPen(QColor(0,0,0));
//    pen.setCosmetic(true);
//    pen.setStyle(Qt::PenStyle::DotLine);
//    painter->setPen(pen);
//    painter->drawRect(this->boundingRect());
//    painter->restore();

}

/**
 * @brief Render all layers of an object. Scalefactor set size multiplier of render output, renderHighQuality() set render quality level.
 * @param painter
 * @param scale
 */
void ItemBase::render(QPainter *painter, qreal scale)
{
    setScaleFactor(scale);

    bool m_hasShadows = hasShadows();
    bool m_hasStrokes = hasStrokes();
    bool m_hasFills = hasFills();
    bool m_hasInnerShadows = hasInnerShadows();

    m_boundingRect = rect();

    // Drop Shadow
    if(m_hasShadows){       

        // create new stroke and fill path only if cache have been invalidated
        if(invalidateCache()){

            if(m_hasFills){
                setShadowMapFill(shape());
            }else setShadowMapFill(QPainterPath());

            if(m_hasStrokes){
                setShadowMapStroke(strokeShape());
            }else setShadowMapStroke(QPainterPath());

            setInvalidateCache(false);
        }

        // Calculate shadow bounding rect
        setBoundingRect(boundingRect().united(ShadowBound(shadowMapStroke())));

        // Draw Drop Shadows
        foreach(Shadow shadow, shadowList()) {
            setBoundingRect(boundingRect().united(drawShadow(shadow, painter)));
        }
    }

    //    QPixmap pm;
    //    if(invalidateCache() == false){
    //        if (m_cache.find(m_cacheKey, &pm)) {
    //            painter->save();
    //            painter->setRenderHint(QPainter::Antialiasing, true);
    //            painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    //            if(shadowMapFill().isEmpty() == false){
    //                QPainterPath clip;
    //                clip.addRect(boundingRect());
    //                clip = PathHandler::combine(clip, shape(), PathHandler::Booleans::Subtract);
    //                painter->setClipPath(clip, Qt::ClipOperation::IntersectClip);
    //            }


    //            painter->drawPixmap(boundingRect(), pm, QRectF(pm.rect()));
    //            painter->restore();
    //            qDebug() << "Draw from Cache";

    //        }
    //    }else {


    //        if(pm.isNull() && shadowList().count() != 0){

    //            qreal tmpLOD = lod();

    //            pm = QPixmap(static_cast<int>(boundingRect().width() * tmpLOD), static_cast<int>(boundingRect().height() * tmpLOD));
    //            pm.fill(Qt::transparent);

    //            QPainter cachePainter(&pm);
    //            cachePainter.scale(tmpLOD, tmpLOD);
    //            cachePainter.translate(QPointF(boundingRect().topLeft().x() * -1,boundingRect().topLeft().y() * -1));

    //            // Draw Shadows
    //            foreach(Shadow shadow, shadowList()) {
    //                setBoundingRect(boundingRect().united(drawShadow(shadow, &cachePainter)));
    //            }

    //            m_cacheKey = m_cache.insert(pm);
    //            painter->save();
    //            painter->setRenderHint(QPainter::Antialiasing, true);
    //            painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    //            if(shadowMapFill().isEmpty() == false){
    //                QPainterPath clip;
    //                clip.addRect(boundingRect());
    //                clip = PathHandler::combine(clip, shape(), PathHandler::Booleans::Subtract);
    //                painter->setClipPath(clip, Qt::ClipOperation::IntersectClip);
    //            }

    //            painter->drawPixmap(boundingRect(), pm, QRectF(pm.rect()));
    //            painter->restore();
    //            setInvalidateCache(false);

    //            qDebug() << "Draw new Pixmap";
    //        }
    //    }


    // Draw Shadows
//    if(shadowList().count() > 0){
//        foreach(Shadow shadow, shadowList()) {
//            setBoundingRect(boundingRect().united(drawShadow(shadow, painter)));
//        }
//    }


    // Draw Fills
    if(m_hasFills){
        foreach(Fills fills,this->fillsList()) {
            drawFills(fills, painter);
        }
    }


    // Draw InnerShadows
    if(m_hasInnerShadows){
        foreach(Shadow shadow, innerShadowList()) {
            drawInnerShadow(shadow, painter);
        }
    }


    // Draw Strokes
    if(m_hasStrokes){
        foreach(Stroke stroke, strokeList()) {
            setBoundingRect(boundingRect().united(drawStrokes(stroke, painter)));
        }
    }

    //    QImage *target = nullptr;
    //       if (painter->paintEngine()->paintDevice()->devType() == QInternal::Image) {
    //           target = static_cast<QImage *>(painter->paintEngine()->paintDevice());

    //           target->save("item.png");
    //       }

}
