#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>
#include <QImage>
#include <QPixmapCache>

#include <itemstruct.h>
#include <stroke.h>
#include <fills.h>
#include <gradient.h>
#include <shadow.h>
#include <abstractitembase.h>

class ItemBase : public AbstractItemBase
{

public:

    ItemBase(const QRectF rect, QGraphicsItem *parent = nullptr);
    ItemBase(const ItemBase &other);


    // operator
    bool operator==( const ItemBase & other ) const;
    inline bool operator!=(const ItemBase &itemBase) const;


    // Properties
	void addStroke(Stroke stroke);
	Stroke stroke(int id = 0) const;
    void updateStroke(Stroke stroke);
	QList<Stroke> strokeList() const;
    bool hasStrokes() const;

	void addFills(Fills fills);
	Fills fills(int id = 0) const;
    void updateFills(Fills fills);
    QList<Fills> fillsList() const;
    bool hasFills() const;

	void addShadow(Shadow shadow);
	Shadow shadow(int id = 0) const;
    void updateShadow(Shadow shadow);
	QList<Shadow> shadowList() const;
    bool hasShadows() const;

	void addInnerShadow(Shadow shadow);
	Shadow innerShadow(int id = 0) const;
    void updateInnerShadow(Shadow shadow);
	QList<Shadow> innerShadowList() const;
    bool hasInnerShadows() const;

    virtual void setRect(QRectF rect) override = 0;
    QRectF renderRect() const override;

    void clipsChildrenToShape(bool doClip);


	// Members
    QPainterPath scaleStroke(const QPainterPath & path, qreal amount , QPen pen = QPen()) const;

    void addItem(AbstractItemBase *item) override;
    void calculateRenderRect();

    // Events
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
	// Properties
    Stroke::StrokePosition m_strokePosition;
    QPainterPath m_shadowPath;
    QRectF m_renderRect;

    // Members
    QList<Fills>                m_fillsList;
    QList<Stroke>               m_strokeList;
    QList<Shadow>               m_shadowList;
    QList<Shadow>               m_innerShadowList;
    QMap<QString,QPainterPath>  m_shadowPathList;
    QMap<QString,QPainterPath>  m_innerShadowPathList;

    bool m_hasFills;
    bool m_hasStrokes;
    bool m_hasInnerShadows;
    bool m_hasShadows;


    qreal lod();
    QPainterPath strokeShape() const;

    // functions    
    QImage blurShadow(QPainterPath shape, QSize size, qreal radius, qreal lod, QPainter::CompositionMode compositionMode, QColor tintColor = Qt::black) const;

    QRectF drawShadow(Shadow shadow, QPainter *painter);
    QRectF drawInnerShadow(Shadow shadow, QPainter *painter);
    QRectF drawFills(Fills fills, QPainter *painter);
    QRectF drawStrokes(Stroke stroke, QPainter *painter);
    QRectF drawBlur(qreal radius, QPainter *painter);

    QRectF calculateShadowPaths();
    void calculateInnerShadowPaths();

};

#endif // ITEMBASE_H
