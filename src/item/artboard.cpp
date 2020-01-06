#include "artboard.h"
#include <QDebug>
#include <QFont>

/*********************
 *
 * Artboard Label
 *
 *********************/

ArtboardLabel::ArtboardLabel(QString name, Artboard *parent) : QGraphicsSimpleTextItem(name, parent)
{
    this->setFlag( QGraphicsItem::ItemIgnoresTransformations, true );
}

void ArtboardLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QStyleOptionGraphicsItem myOption(*option);
    myOption.state &= ~QStyle::State_Selected;
    QGraphicsSimpleTextItem::paint(painter, &myOption, widget);
}

void ArtboardLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->parentItem()->setFlag( QGraphicsItem::ItemIsSelectable, true );
    this->parentItem()->setSelected(true);
}


/*******************************************************************************************************************************/

/*********************
 *
 * Artboard
 *
 *********************/

Artboard::Artboard(QString name, QGraphicsItem *parent) : Artboard(name, 0,0,375,667, parent){}
Artboard::Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent) : Artboard(name, QRectF(x,y,w,h), parent){}
Artboard::Artboard(QString name, QRectF rect, QGraphicsItem *parent) : AbstractItemBase(rect, parent)
{
    m_offset= 24;
    m_buffer = 4;
    m_backgroundColor = Qt::white;
    m_useBGColor = true;
    m_doRender = false;

    m_artboard = new QGraphicsRectItem(rect);
    m_artboard->setFlags(
                QGraphicsItem::ItemClipsChildrenToShape /*|
                                        QGraphicsItem::ItemContainsChildrenInShape |
                                        QGraphicsItem::ItemSendsScenePositionChanges |
                                        QGraphicsItem::ItemSendsGeometryChanges*/
                );
    m_artboard->setPen(Qt::NoPen);
    m_artboard->setBrush(Qt::NoBrush);
    m_artboard->setParentItem(this);

    m_label = new ArtboardLabel(name, this);


    this->setFlag( QGraphicsItem::ItemIsSelectable, false );
    //    this->setFlag( QGraphicsItem::ItemSendsScenePositionChanges, true );
    //    this->setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );

    this->setAcceptHoverEvents(true);
    this->setName(name);
    //this->setItemType(ItemType::Artboard);

}

Artboard::Artboard(const Artboard &other) : AbstractItemBase(other)
{
    m_offset = other.m_offset;
    m_buffer = other.m_buffer;
    m_useBGColor = other.m_useBGColor;
    m_backgroundColor = other.m_backgroundColor;
    m_label = other.m_label;
    m_artboard = other.m_artboard;
}

bool Artboard::operator==(const Artboard &other) const
{
    if(this == &other) return true;

    return m_offset == other.m_offset &&
            m_buffer == other.m_buffer &&
            m_useBGColor == other.m_useBGColor &&
            m_backgroundColor == other.m_backgroundColor &&
            m_label == other.m_label &&
            m_artboard == other.m_artboard &&
            AbstractItemBase::operator==(other);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QGraphicsRectItem * Artboard::canvas() const
{
    return m_artboard;
}

void Artboard::setRect(QRectF rect)
{
    QPainterPath shape;
    shape.addRect(rect);
    AbstractItemBase::setShape(shape);
    m_artboard->setRect(rect);
    m_artboard->update();
}


/*!
 * \brief Add item to artboard canvas.
 * \param item
 */
void Artboard::addItem(AbstractItemBase *item)
{
    item->setParentItem(m_artboard);
}


/*!
 * \brief Return list of first level children items.
 * \return
 */
QList<AbstractItemBase *> Artboard::childItems() const
{
    QList<AbstractItemBase*> aibList;

    foreach(QGraphicsItem * item, m_artboard->childItems()){
        AbstractItemBase * abItem = dynamic_cast<AbstractItemBase*>(item);
        if(abItem) aibList.append(abItem);
    }
    return aibList;
}


QRectF Artboard::renderRect() const
{
    return m_rect;
}

void Artboard::setBackgroundColor(const QColor color)
{
    m_backgroundColor = color;
}

QColor Artboard::backgroundColor() const
{
    return m_backgroundColor;
}

void Artboard::setUseBackgroundColor(bool useBGColor)
{
    m_useBGColor = useBGColor;
}

bool Artboard::useBackgroundColor() const
{
    return m_useBGColor;
}


/***************************************************
 *
 * Events
 *
 ***************************************************/

void Artboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(m_useBGColor) painter->fillRect(renderRect(), QBrush(m_backgroundColor));

    m_scaleFactor = option->levelOfDetailFromTransform( painter->transform());

    if(!m_doRender){
        qreal offset = m_offset/m_scaleFactor;
        m_boundingRect = rect().adjusted( -m_buffer, -offset - m_buffer, m_buffer, m_buffer);
        m_label->setPos(this->rect().x(), this->rect().y() -offset);

        QPen pen = QPen(QColor(200,200,200));
        pen.setCosmetic(true);

        painter->setBrush(QBrush(m_backgroundColor));
        painter->setPen(pen);
        painter->drawRect(this->rect());
    }

}

void Artboard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    this->setSelected(false);
}

void Artboard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    this->setSelected(false);
}
