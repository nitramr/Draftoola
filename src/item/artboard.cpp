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
    //dynamic_cast<Artboard*>(this->parentItem())->canvas()->setSelected(true);
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
                QGraphicsItem::ItemClipsChildrenToShape |
                QGraphicsItem::ItemContainsChildrenInShape |
                QGraphicsItem::ItemSendsScenePositionChanges |
                QGraphicsItem::ItemSendsGeometryChanges
                );
    m_artboard->setPen(Qt::NoPen);
    m_artboard->setBrush(Qt::NoBrush);
    m_artboard->setParentItem(this);

    m_label = new ArtboardLabel(name, this);


    this->setFlag( QGraphicsItem::ItemIsSelectable, true );
//    this->setFlag( QGraphicsItem::ItemSendsScenePositionChanges, true );
//    this->setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );

    this->setAcceptHoverEvents(true);
    this->setName(name);
    this->setItemType(ItemType::Artboard);

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
    m_children.append(item);

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

void Artboard::setDoRender(bool doRender)
{
    m_doRender = doRender;
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

    qreal offset = m_offset/scaleFactor();

    setBoundingRect(rect().adjusted( -m_buffer, -offset - m_buffer, m_buffer, m_buffer));

    m_label->setPos(this->rect().x(), this->rect().y() -offset);

    if(m_useBGColor) painter->fillRect(canvas()->rect(), QBrush(m_backgroundColor));

    if(!m_doRender){
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

void Artboard::render(QPainter *painter, qreal scale)
{
    setScaleFactor(scale);

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    m_doRender = true;
    paint(painter, nullptr);
    m_doRender = false;

    QList<QGraphicsItem*> list = canvas()->childItems();

    foreach(QGraphicsItem *object, list){
        AbstractItemBase *abItem = static_cast<AbstractItemBase*>(object);
        if(abItem){
            abItem->setHighRenderQuality(true);
            painter->translate(abItem->pos());
            abItem->render(painter, scale );
            abItem->setHighRenderQuality(false);
            painter->translate(-abItem->pos());
        }
    }

    painter->restore();

}

