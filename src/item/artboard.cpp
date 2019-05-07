#include "artboard.h"
#include <QDebug>
#include <QFont>

/*********************
 *
 * Artboard Label
 *
 *********************/

ArtboardLabel::ArtboardLabel(QString name, Artboard *parent) : QGraphicsTextItem(name)
{

//    this->setFlag( QGraphicsItem::ItemIsFocusable, true );
    this->setFlag( QGraphicsItem::ItemIgnoresTransformations, true );
//    this->setFlag( QGraphicsItem::ItemIsSelectable, true );

    this->setTextInteractionFlags(Qt::NoTextInteraction);
}

void ArtboardLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QStyleOptionGraphicsItem myOption(*option);
        myOption.state &= ~QStyle::State_Selected;
    QGraphicsTextItem::paint(painter, &myOption, widget);
}

void ArtboardLabel::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    setTextInteractionFlags(Qt::NoTextInteraction);
}

void ArtboardLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //	Q_UNUSED(event);

    if (this->textInteractionFlags() == Qt::NoTextInteraction)
        this->setTextInteractionFlags(Qt::TextEditorInteraction);
    setFocus();
    QGraphicsTextItem::mouseDoubleClickEvent(event);
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

    m_artboard = new QGraphicsRectItem(rect);
    m_artboard->setFlags(
                QGraphicsItem::ItemClipsChildrenToShape |
                QGraphicsItem::ItemContainsChildrenInShape |
                QGraphicsItem::ItemSendsScenePositionChanges |
                QGraphicsItem::ItemSendsGeometryChanges
                );
    m_artboard->setPen(Qt::NoPen);
    m_artboard->setBrush(Qt::NoBrush);
    m_artboard->setParentItem(this);

    m_label = new ArtboardLabel(name, this);
    m_label->setParentItem(this);


    this->setFlag( QGraphicsItem::ItemIsSelectable, true );
    this->setFlag( QGraphicsItem::ItemSendsScenePositionChanges, true );
    this->setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );

    this->setAcceptHoverEvents(true);
    this->setName(name);
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

void Artboard::addItem(AbstractItemBase *item)
{
    item->setParentItem(m_artboard);
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

    setBoundingRect(rect().adjusted( -m_buffer, -m_offset/scaleFactor() - m_buffer, m_buffer, m_buffer));

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    // zoom level
    //	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    m_label->setPos(this->rect().x(), this->rect().y() - m_offset/scaleFactor());

    // draw border outside of canvas
    QPen pen = QPen(QColor(200,200,200));
    pen.setCosmetic(true);

    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(this->rect());

    // reset painter
    painter->restore();

    // BoundingBox
//    painter->save();
//    QPen penB = QPen(QColor(0,0,0));
//    penB.setCosmetic(true);
//    penB.setStyle(Qt::PenStyle::DotLine);
//    painter->setPen(penB);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(this->boundingRect());
//    painter->restore();

}

