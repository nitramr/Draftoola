#include "abstractitembase.h"
#include <QDebug>
#include <QPainter>
#include <QtWidgets>

AbstractItemBase::AbstractItemBase() : AbstractItemBase(QRect()){}
AbstractItemBase::AbstractItemBase(const QRectF rect, QGraphicsItem *parent) : QGraphicsObject(parent)
{
    m_name = "";
    m_lod = 1;
    m_boundingRect = rect;
    m_exportFactorList = QList<ExportLevel>();
    m_frameType = FrameType::Free;
    m_invaliateCache = true;
    m_doRender = false;

    setRenderQuality(RenderQuality::Optimal);

    QRandomGenerator *random = QRandomGenerator::global();
    quint32 value32 = random->generate();
    QString hexvalue = QString("0x%1").arg(value32, 8, 16, QLatin1Char( '0' ));

    m_id = hexvalue; //static_cast<int>(value32);

    QPainterPath path;
    path.addRect(rect);
    setShape(path);

    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

}

AbstractItemBase::AbstractItemBase(const AbstractItemBase &other) : QGraphicsObject(other.parentItem())
{        
    m_id = other.m_id;
    m_rect = other.m_rect;
    m_name = other.m_name;
    m_frameType = other.m_frameType;
    m_lod = other.m_lod;
    m_renderQuality = other.m_renderQuality;
    m_boundingRect = other.m_boundingRect;
    m_exportFactorList = other.m_exportFactorList;
    m_shape = other.m_shape;
    m_invaliateCache = other.m_invaliateCache;
    m_exportFactorList = other.m_exportFactorList;

    this->setFlags(other.flags());
    this->setPos(other.pos());
    this->setTransform(other.transform());
    this->setScale(other.scale());

}



/***************************************************
 *
 * Properties
 *
 ***************************************************/

void AbstractItemBase::setID(QString id)
{
    m_id = id;
}

QString AbstractItemBase::ID() const
{
    return m_id;
}

void AbstractItemBase::setName(QString name)
{
    m_name = name;
}

QString AbstractItemBase::name() const
{
    return m_name;
}

void AbstractItemBase::setInvalidateCache(bool invalidate)
{
    m_invaliateCache = invalidate;
}

bool AbstractItemBase::invalidateCache() const
{
    return m_invaliateCache;
}


void AbstractItemBase::setShape(QPainterPath itemShape)
{
    m_shape = itemShape;
    m_rect = m_shape.boundingRect().normalized();
    setInvalidateCache(true);
    qDebug() << "Invalidate::setShape()";
    setTransformOriginPoint(m_rect.center());

    //    emit this->widthChanged();
    //    emit this->heightChanged();

    update();
}

/*!
 * \brief Return path shape of the object.
 * \return
 */
QPainterPath AbstractItemBase::shape() const
{
    return m_shape;
}

/*!
 * \brief Return a rectangle that covers only the base shape of the object.
 * \return
 */
QRectF AbstractItemBase::rect() const
{
    return m_rect;
}

/*!
 * \brief Return a rectangle that covers all rendered areas of the object.
 * \return
 */
QRectF AbstractItemBase::boundingRect() const
{
    return m_rect; //m_boundingRect;
}


void AbstractItemBase::setFrameType(FrameType frameType)
{
    m_frameType = frameType;
}


AbstractItemBase::FrameType AbstractItemBase::frameType()
{
    return m_frameType;
}


void AbstractItemBase::setRenderQuality(RenderQuality qualityLevel)
{
    m_renderQuality = qualityLevel;

    switch(m_renderQuality){
    case RenderQuality::Performance:
        QGraphicsItem::setCacheMode(QGraphicsItem::ItemCoordinateCache);
        break;
    case RenderQuality::Optimal:
    case RenderQuality::Quality:
        QGraphicsItem::setCacheMode(QGraphicsItem::NoCache);
        break;
    }

}

AbstractItemBase::RenderQuality AbstractItemBase::renderQuality() const
{
    return m_renderQuality;
}


QPointF AbstractItemBase::anchorTopLeft() const
{
    return this->scenePos();
}

QPointF AbstractItemBase::anchorTop() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y());
}

QPointF AbstractItemBase::anchorTopRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y());
}

QPointF AbstractItemBase::anchorRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height() / 2);
}

QPointF AbstractItemBase::anchorBottomRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorBottom() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorBottomLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height() / 2);
}

QPointF AbstractItemBase::anchorCenter() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height() / 2);
}

/***************************************************
 *
 * Members
 *
 ***************************************************/


void AbstractItemBase::addExportLevel(ExportLevel exportLevel, int index){
    if(index < 0){
        m_exportFactorList.append(exportLevel);
    }else m_exportFactorList.insert(index, exportLevel);
}

void AbstractItemBase::removeExportLevel(int index){
    m_exportFactorList.removeAt(index);
}

void AbstractItemBase::removeExportLevel(ExportLevel exportLevel)
{
    m_exportFactorList.removeOne(exportLevel);
}

void AbstractItemBase::updateExportLevel(ExportLevel exportLevel)
{
    for(int i=0; i < m_exportFactorList.count(); i++){
        ExportLevel m_property = m_exportFactorList.at(i);
        if(m_property.ID() == exportLevel.ID()){
            m_exportFactorList.replace(i,exportLevel);
            return;
        }
    }
}

QList<ExportLevel> AbstractItemBase::exportLevels() const
{
    return m_exportFactorList;
}

ExportLevel AbstractItemBase::exportLevel(int index)
{
    return m_exportFactorList.value(index);
}

QList<AbstractItemBase *> AbstractItemBase::childItems() const
{
    QList<AbstractItemBase*> aibList;

    foreach(QGraphicsItem * item, QGraphicsItem::childItems()){
        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(item);
        if(abItem) aibList.append(abItem);
    }

    return aibList;
}


/**
 * @brief Render all layers of an object. Scalefactor set size multiplier of render output, renderHighQuality() set render quality level.
 * @param painter
 * @param scale
 */
void AbstractItemBase::render(QPainter *painter)
{

//    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    this->setInvalidateCache(true);

    RenderQuality renderState = renderQuality();
    m_doRender = true;
    setRenderQuality(RenderQuality::Quality);
    paint(painter, new QStyleOptionGraphicsItem());
    m_doRender = false;
    setRenderQuality(renderState);


    QList<AbstractItemBase*> list = this->childItems();

    foreach(AbstractItemBase *abItem, list){

        if(abItem){
            painter->translate(abItem->pos());
            abItem->render(painter);
            painter->translate(-abItem->pos());
        }
    }

//    painter->restore();
}

/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool AbstractItemBase::operator==(const AbstractItemBase &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_rect == other.m_rect &&
            m_name == other.m_name &&
            m_frameType == other.m_frameType &&
            m_exportFactorList == other.m_exportFactorList &&
            m_shape == other.m_shape &&
            flags() == other.flags() &&
            pos() == other.pos() &&
            transform() == other.transform() &&
            scale() == other.scale();

}


QDebug operator<<(QDebug dbg, const AbstractItemBase &obj)
{

    dbg << obj.m_id <<
           obj.m_rect <<
           obj.m_name <<
           obj.m_frameType <<
           obj.m_exportFactorList <<
           obj.m_shape;

    dbg << obj.flags() <<
           obj.pos() <<
           obj.transform() <<
           obj.scale();


    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const AbstractItemBase &obj)
{
    out << obj.m_id <<
           obj.m_rect <<
           obj.m_name <<
           (int)obj.m_frameType <<
           obj.m_exportFactorList <<
           obj.m_shape;

    out << obj.flags() <<
           obj.pos() <<
           obj.transform() <<
           obj.scale();

    return out;
}

QDataStream &operator>>(QDataStream &in, AbstractItemBase &obj)
{
    QString id;
    QRectF rect;
    int frameType;
    QString name;
    QPainterPath shape;
    QList<ExportLevel>	exportFactorList;
    QGraphicsItem::GraphicsItemFlags flags;
    QPointF pos;
    QTransform transform;
    double scale;

    in >> id >> rect >> name >> frameType >> exportFactorList >> shape >> flags >> pos >> transform >> scale;

    obj.setID(id);
    obj.setShape(shape);
    obj.setRect(rect);
    obj.setName(name);
    obj.setFrameType(AbstractItemBase::FrameType(frameType));
    foreach(ExportLevel expLevel, exportFactorList){
        obj.addExportLevel(expLevel);
    }

    obj.setFlags(flags);
    obj.setPos(pos);
    obj.setTransform(transform);
    obj.setScale(scale);


    return in;
}
