#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>


class WAScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WAScene(QObject *parent = 0);

private:


protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);
	void drawForeground(QPainter *painter, const QRectF &rect);

};

#endif // WASCENE_H
