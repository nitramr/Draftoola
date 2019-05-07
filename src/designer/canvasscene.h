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

	void render(QPainter *painter,
					const QRectF &target = QRectF(), const QRectF &source = QRectF(),
						Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);


    AbstractItemBase *itemByName(const QString name);

    qreal scaleFactor() const;
    void setScaleFactor(qreal factor);

    void exportItems();
    void exportItem(AbstractItemBase *item);

private:
    qreal m_scaleFactor;


protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);
    void drawBackground(QPainter *painter, const QRectF &rect);
	void drawForeground(QPainter *painter, const QRectF &rect);


};

#endif // WASCENE_H
