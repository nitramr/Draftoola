#include <artboard.h>
#include <QDebug>
#include <QFont>
#include <QGraphicsDropShadowEffect>

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
    Q_UNUSED(event)

    this->parentItem()->setFlag( QGraphicsItem::ItemIsSelectable, true );
    this->parentItem()->setSelected(true);
    this->parentItem()->setFocus();

}

/*******************************************************************************************************************************/

/*********************
 *
 * Artboard
 *
 *********************/

Artboard::Artboard() : Artboard(QString()){}
Artboard::Artboard(QString name, QGraphicsItem *parent) : Artboard(name, 0,0,375,667, parent){}
Artboard::Artboard(QString name, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent) : Artboard(name, QRectF(x,y,w,h), parent){}
Artboard::Artboard(QString name, QRectF rect, QGraphicsItem *parent) : AbstractItemBase(rect, parent)
{
    m_offset= 24;
    m_buffer = 4;
    m_backgroundColor = Qt::white;
    m_useBGColor = true;

    m_artboard = new ArtboardCanvas(rect, this);
    m_artboard->setFlags(
                QGraphicsItem::ItemClipsChildrenToShape /*|
                                                                QGraphicsItem::ItemContainsChildrenInShape |
                                                                QGraphicsItem::ItemSendsScenePositionChanges |
                                                                QGraphicsItem::ItemSendsGeometryChanges*/
                );
    m_artboard->setPen(Qt::NoPen);
    m_artboard->setBrush(Qt::NoBrush);
    m_artboard->setFocusProxy(this);

    m_label = new ArtboardLabel(name, this);

    setRenderQuality(RenderQuality::Quality);


    this->setFlag( QGraphicsItem::ItemIsSelectable, false );
    //    this->setFlag( QGraphicsItem::ItemSendsScenePositionChanges, true );
    //    this->setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );

    this->setAcceptHoverEvents(true);
    this->setName(name);

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

    switch(frameType()){
    case AbstractItemBase::FixedWidth:
        rect.setWidth(this->rect().width());
        break;
    case AbstractItemBase::FixedHeight:
        rect.setHeight(this->rect().height());
        break;
    case AbstractItemBase::FixedSize:
        rect = this->rect();
        break;
    case AbstractItemBase::Free:
        break;
    }

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

void Artboard::setName(QString text)
{
    m_label->setText(text);
    m_name = text;
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
    Q_UNUSED(widget);

    if(m_useBGColor) painter->fillRect(renderRect(), QBrush(m_backgroundColor));

    m_lod = option->levelOfDetailFromTransform( painter->transform());

    if(!m_doRender){
        qreal offset = m_offset/m_lod;
        m_boundingRect = rect().adjusted( -m_buffer, -offset - m_buffer, m_buffer, m_buffer);

        if(m_lod > 0.15){
            m_label->setPos(this->rect().x(), this->rect().y() -offset);
            m_label->show();
        }else m_label->hide();


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

/***************************************************
 *
 * Operator
 *
 ***************************************************/

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

void Artboard::fromObject(AbstractItemBase *obj)
{
    m_id = obj->m_id;
    m_rect = obj->m_rect;
    m_name = obj->m_name;
    m_frameType = obj->m_frameType;
    m_exportFactorList = obj->m_exportFactorList;
    m_shape = obj->m_shape;
    setFlags(obj->flags());
    setPos(obj->pos());
    setTransform(obj->transform());
    setScale(obj->scale());
}


QDebug operator<<(QDebug dbg, const Artboard &obj)
{
    const AbstractItemBase &aib = obj;

    dbg << aib <<
           obj.m_useBGColor <<
           obj.m_backgroundColor <<
           obj.m_label->text();

    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Artboard &obj)
{
    const AbstractItemBase &aib = obj;

    out << aib <<
           obj.m_useBGColor <<
           obj.m_backgroundColor <<
           obj.m_label->text();

    return out;
}

QDataStream &operator>>(QDataStream &in, Artboard &obj)
{
    bool useBGColor;
    QColor bgColor;
    QString text;
    AbstractItemBase *aib = nullptr;

    in >> *aib >> useBGColor >> bgColor >> text;

   obj.fromObject(aib);
   obj.setBackgroundColor(bgColor);
   obj.setUseBackgroundColor(useBGColor);
   obj.setName(aib->name());

    return in;
}

