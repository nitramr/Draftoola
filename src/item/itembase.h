#ifndef ITEMBASE_H
#define ITEMBASE_H

//#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>
#include <QImage>
#include <QPixmapCache>

#include "itemstruct.h"
#include "stroke.h"
#include "fills.h"
#include "gradient.h"
#include "shadow.h"
#include "abstractitembase.h"

//#include <QGraphicsDropShadowEffect>


class ItemBase : public AbstractItemBase
{

public:

    ItemBase(const QRectF rect, QGraphicsItem *parent = nullptr);

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

    QRectF renderRect() const override;

	// Members
    QPainterPath scaleStroke(const QPainterPath & path, qreal amount , QPen pen = QPen()) const;

    void addItem(AbstractItemBase *item) override;

    // Events
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void render(QPainter *painter, qreal scale = 1) override;

private:
	// Properties
	StrokePosition m_strokePosition;
    bool m_renderQuality;
    QPainterPath m_shadowMapStroke;
    QPainterPath m_shadowMapFill;
//    QGraphicsDropShadowEffect * qShadow;
    QPixmapCache m_cache;
    mutable QPixmapCache::Key m_cacheKey;

    // Members
    QList<Fills>			m_fillsList;
    QList<Stroke>			m_strokeList;
    QList<Shadow>			m_shadowList;
    QList<Shadow>			m_innerShadowList;

    qreal lod() const;

    void setShadowMapStroke(const QPainterPath &shape);
    QPainterPath shadowMapStroke() const;

    void setShadowMapFill(const QPainterPath &shape);
    QPainterPath shadowMapFill() const;

    QPainterPath strokeShape() const;

    // functions    
    QImage blurShadow(QPainterPath shape, QSize size, qreal radius, qreal lod, QPainter::CompositionMode compositionMode, QColor tintColor = Qt::black) const;
    QRectF ShadowBound(QPainterPath shape) const;

    QRectF drawShadow(Shadow shadow, QPainter *painter);
    QRectF drawInnerShadow(Shadow shadow, QPainter *painter);
    QRectF drawFills(Fills fills, QPainter *painter);
    QRectF drawStrokes(Stroke stroke, QPainter *painter);
    QRectF drawBlur(qreal radius, QPainter *painter);

};

#endif // ITEMBASE_H
