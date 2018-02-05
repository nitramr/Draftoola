#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

class WAScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WAScene(QObject *parent = 0);

	void render(QPainter *painter,
					const QRectF &target = QRectF(), const QRectF &source = QRectF(),
						Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);

	ItemBase *itemByName(const QString name);

private:


protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);
	void drawForeground(QPainter *painter, const QRectF &rect);

};

#endif // WASCENE_H
