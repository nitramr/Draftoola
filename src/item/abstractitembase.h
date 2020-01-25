#ifndef ABSTRACTITEMBASE_H
#define ABSTRACTITEMBASE_H

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <QMap>
#include <QList>

#include <itemstruct.h>
#include <exportlevel.h>

class AbstractItemBase : public QGraphicsObject
{

    friend class ItemBase;
    friend class Artboard;
    friend class ItemPolygon;
    friend class ItemText;

public:

    // Enums
    enum Type { Artboard = UserType + 2,
           Rect = UserType + 3,
           Oval = UserType + 4,
           Polygon = UserType + 5,
           Path = UserType + 6,
           Line = UserType + 7,
           Text = UserType + 8,
           Instance = UserType + 9,
           Group = UserType + 10
         };

    enum FrameType {
        Free = 0,
        FixedWidth = 1,
        FixedHeight = 2,
        FixedSize = 3
    };

    enum RenderQuality {
        Balanced = 0,
        Performance = 1,
        Quality = 2
    };


    // Constructor
    AbstractItemBase();
    AbstractItemBase(const QRectF rect, QGraphicsItem *parent = nullptr);
    AbstractItemBase(const AbstractItemBase &other);


    // operator
    bool operator==( const AbstractItemBase & other ) const;
    inline bool operator!=(const AbstractItemBase &abstractItemBase) const;
    friend QDataStream &operator<<(QDataStream &out, const AbstractItemBase &obj);
    friend QDataStream &operator>>(QDataStream &in, AbstractItemBase &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const AbstractItemBase &obj);
#endif


    // Properties
    void setID(QString id);
    QString ID() const;

    virtual void setName(QString name);
    QString name() const;

    virtual void setShape(QPainterPath itemShape);
    virtual QPainterPath shape() const override;

    virtual void setRect(QRectF rect) = 0;
    virtual QRectF rect() const;
    virtual QRectF boundingRect() const override;
    virtual QRectF renderRect() const = 0;

    void setFrameType(FrameType frameType );
    FrameType frameType();

    RenderQuality renderQuality() const;

    void setInvalidateCache(bool invalidate);
    bool invalidateCache() const;

    QPointF anchorTopLeft() const;
    QPointF anchorTop() const;
    QPointF anchorTopRight() const;
    QPointF anchorRight() const;
    QPointF anchorBottomRight() const;
    QPointF anchorBottom() const;
    QPointF anchorBottomLeft() const;
    QPointF anchorLeft() const;
    QPointF anchorCenter() const;


    // Members
    void addExportLevel(ExportLevel exportLevel, int index = -1);
    void removeExportLevel(int index);
    void removeExportLevel(ExportLevel exportLevel);
    void updateExportLevel(ExportLevel exportLevel);
    QList<ExportLevel> exportLevels() const;
    ExportLevel exportLevel(int index);

    virtual QList<AbstractItemBase*> childItems() const;


    // Functions
    virtual void addItem(AbstractItemBase * childItems) = 0;


    // Events
    virtual void render(QPainter *painter);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

//public slots:
    void setRenderQuality(RenderQuality qualityLevel);


private:

    // Properties
    QString m_id;
    QRectF m_rect;
    QRectF m_boundingRect;
    FrameType m_frameType;
    QString m_name;
    bool m_invaliateCache;
    qreal m_lod;
    RenderQuality m_renderQuality;
    QPainterPath m_shape;
    bool m_doRender;
    bool m_isHovered;

    // Members
    QList<ExportLevel>	m_exportFactorList;

signals:
  //  void isHovered(bool);

};

#endif // ABSTRACTITEMBASE_H
