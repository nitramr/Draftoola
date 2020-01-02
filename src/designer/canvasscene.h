#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>

#include "src/item/itembase.h"
#include "src/item/artboard.h"

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CanvasScene(QObject *parent = nullptr);

    qreal scaleFactor() const;
    void setScaleFactor(qreal factor);

public slots:
    void exportItems();
    void exportItem(AbstractItemBase *item);

private:
    qreal m_scaleFactor;
    int m_grid;
    QPainterPath m_hoverPath;
    QPointF m_hoverPoint;

    void saveImage(AbstractItemBase *bi, qreal multiplier, const QString outputPath, QColor bgColor = Qt::transparent);
    void saveSVG(AbstractItemBase *bi, const QString outputPath);
    void savePDF(AbstractItemBase *bi, const QString outputPath);

protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);
    void drawBackground(QPainter *painter, const QRectF &rect);
	void drawForeground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // WASCENE_H
