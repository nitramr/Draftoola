#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QGraphicsItemGroup>
#include "abstractitembase.h"

class ItemGroup : public AbstractItemBase
{

public:
    explicit ItemGroup(QGraphicsItem *parent = nullptr);

	// Properties
    int type() const override { return Type::Group; }
    void setRect(QRectF rect) override;
    QRectF renderRect() const override;
    QRectF rect() const override;
    QRectF boundingRect() const override;

    // Member
    void addItem(AbstractItemBase *childItems) override;
    QList<AbstractItemBase*> childItems() const;

    // Events
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void render(QPainter *painter, qreal scale = 1) override;

private:
//    QGraphicsItemGroup * m_group;
    QList<AbstractItemBase*> m_children;
    QRectF m_renderRect;
    QRectF m_rect;

signals:

public slots:
};

#endif // WAGROUP_H
