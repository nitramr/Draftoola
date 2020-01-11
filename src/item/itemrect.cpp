#include <itemrect.h>

ItemRect::ItemRect(QGraphicsItem *parent) : ItemRect(0,0,80,80, parent){}
ItemRect::ItemRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : ItemRect(QRectF(x,y,width,height), parent){}
ItemRect::ItemRect(qreal width, qreal height, QGraphicsItem *parent) : ItemRect(QRectF(0,0,width,height), parent){}
ItemRect::ItemRect(QRectF rect, QGraphicsItem *parent) : ItemBase(rect, parent){

    m_radiusTL = 0;
    m_radiusTR = 0;
    m_radiusBR = 0;
    m_radiusBL = 0;

    this->setRect(rect);
    this->setName(tr("Rect"));

}

ItemRect::ItemRect(const ItemRect &other) : ItemBase(other)
{
    m_radiusTL = other.m_radiusTL;
    m_radiusTR = other.m_radiusTR;
    m_radiusBR = other.m_radiusBR;
    m_radiusBL = other.m_radiusBL;
}

bool ItemRect::operator==(const ItemRect &other) const
{
    if(this == &other) return true;

    return m_radiusTL == other.m_radiusTL &&
            m_radiusTR == other.m_radiusTR &&
            m_radiusBR == other.m_radiusBR &&
            m_radiusBL == other.m_radiusBL &&
            ItemBase::operator==(other);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemRect::setRadius(qreal radius)
{
    setRadius(radius, radius, radius, radius);
}

void ItemRect::setRadius(qreal topleft, qreal topright, qreal bottomright, qreal bottomleft)
{
    m_radiusTL = topleft;
    m_radiusTR = topright;
    m_radiusBR = bottomright;
    m_radiusBL = bottomleft;

    setRect(this->rect());
}

void ItemRect::setRect(QRectF rect)
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

    ItemBase::setShape(shapeScaled(rect)); // setRect() will set by setShape()
}

QPainterPath ItemRect::shapeScaled(QRectF frame) const
{
    QPainterPath path;

    qreal l = frame.left();
    qreal t = frame.top();
    qreal r = frame.right();
    qreal b = frame.bottom();
    qreal w = frame.width() / 2;
    qreal h = frame.height() / 2;
    qreal tl = m_radiusTL;
    qreal tr = m_radiusTR;
    qreal br = m_radiusBR;
    qreal bl = m_radiusBL;

    if (w <= 0 || h <= 0) {
        bl = 0;
        br = 0;
        tr = 0;
        tl = 0;
    } else {
        qreal blW, blH;
        blW = qMin(bl, w);
        blH = qMin(bl, h);
        bl = qMin(blH, blW);

        qreal brW, brH;
        brW = qMin(br, w);
        brH = qMin(br, h);
        br = qMin(brH, brW);

        qreal trW, trH;
        trW = qMin(tr, w);
        trH = qMin(tr, h);
        tr = qMin(trH, trW);

        qreal tlW, tlH;
        tlW = qMin(tl, w);
        tlH = qMin(tl, h);
        tl = qMin(tlH, tlW);
    }

    tl = tl*2;
    tr = tr*2;
    br = br*2;
    bl = bl*2;

    path.arcMoveTo(l, t, tl, tl, 180);
    if(tl<=0){
        path.lineTo(l, t);
    }else path.arcTo(l, t, tl, tl, 180, -90); // TL

    if(tr<=0){
        path.lineTo(r, t);
    }else path.arcTo(r-tr, t, tr, tr, 90, -90); // TR

    if(br<=0){
        path.lineTo(r, b);
    }else path.arcTo(r-br, b-br, br, br, 0, -90); // BR

    if(bl<=0){
        path.lineTo(l, b);
    }else path.arcTo(l, b-bl, bl, bl, 270, -90); // BL

    path.closeSubpath();

    return path;
}


