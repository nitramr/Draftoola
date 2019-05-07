#include "abstractitembase.h"
#include <QDebug>
#include <QPainter>
#include <QtWidgets>

AbstractItemBase::AbstractItemBase(const QRectF rect, QGraphicsItem *parent) : QGraphicsObject(parent)
{
    m_itemType = ItemType::Rect;
    m_name = "";
    m_id = -1;
    m_scaleFactor = 1;
    m_renderQuality = false;
    m_boundingRect = rect;
    m_exportFactorList = QList<ExportLevel>();

    QPainterPath path;
    path.addRect(rect);
    setShape(path);

}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void AbstractItemBase::setID(int id)
{
    m_id = id;
}

int AbstractItemBase::ID() const
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

void AbstractItemBase::setItemType(ItemType type)
{
    m_itemType = type;
}

ItemType AbstractItemBase::itemType() const
{
    return m_itemType;
}

void AbstractItemBase::setInvalidateCache(bool invalidate)
{
    m_invaliateCache = invalidate;
}

bool AbstractItemBase::invalidateCache() const
{
    return m_invaliateCache;
}

void AbstractItemBase::setScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

qreal AbstractItemBase::scaleFactor() const
{
    return m_scaleFactor;
}

void AbstractItemBase::setShape(QPainterPath itemShape)
{
    m_shape = itemShape;
    m_rect = m_shape.boundingRect().normalized();
    setInvalidateCache(true);
    this->setTransformOriginPoint(m_rect.center());
    update();
}

QPainterPath AbstractItemBase::shape() const
{
    return m_shape;
}

QRectF AbstractItemBase::rect() const
{
    return m_rect;
}

void AbstractItemBase::setBoundingRect(QRectF boundingrect)
{
    m_boundingRect = boundingrect;
}

QRectF AbstractItemBase::boundingRect() const
{
    return m_boundingRect;
}

void AbstractItemBase::setHighRenderQuality(bool isHighResolution)
{
    m_renderQuality = isHighResolution;
}

bool AbstractItemBase::highRenderQuality() const
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

/***************************************************
 *
 * Events
 *
 ***************************************************/

//void AbstractItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);

//    setScaleFactor(option->levelOfDetailFromTransform(painter->transform()));

    // reset bounding box to minimum shape
//   m_boundingRect = rect();

//}

