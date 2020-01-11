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


    // Constructor
    AbstractItemBase(const QRectF rect, QGraphicsItem *parent = nullptr);
    AbstractItemBase(const AbstractItemBase &other);


    // operator
    bool operator==( const AbstractItemBase & other ) const;
    inline bool operator!=(const AbstractItemBase &abstractItemBase) const;


    // Properties
    void setID(int id);
    int ID() const;

    void setName(QString name);
    QString name() const;

    virtual void setShape(QPainterPath itemShape);
    virtual QPainterPath shape() const override;

    virtual void setRect(QRectF rect) = 0;
    virtual QRectF rect() const;
    virtual QRectF boundingRect() const override;
    virtual QRectF renderRect() const = 0;

    void setFrameType(FrameType frameType );
    FrameType frameType();

    bool highRenderQuality() const;

    void setInvalidateCache(bool invalidate);
    bool invalidateCache() const;

    qreal scaleFactor() const;

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
    virtual void render(QPainter *painter, qreal scale = 1);

public slots:
    void setScaleFactor(qreal scaleFactor);
    void setHighRenderQuality(bool isHighResolution);


private:

    // Properties
    int m_id;
    QRectF m_rect;
    QRectF m_boundingRect;
    FrameType m_frameType;
    QString m_name;
    bool m_invaliateCache;
    qreal m_scaleFactor;
    bool m_renderQuality;
    bool m_doRender;
    QPainterPath m_shape;


    // Members
    QList<ExportLevel>	m_exportFactorList;

};

#endif // ABSTRACTITEMBASE_H
