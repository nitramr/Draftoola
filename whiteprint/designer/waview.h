#ifndef WAVIEW_H
#define WAVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

#include "wascene.h"
#include "handleframe.h"

class WAView : public QGraphicsView
{
    Q_OBJECT
public:
	WAView(WAScene *scene, QWidget * parent = 0);
	HandleFrame *handleFrame() const;

protected:
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent * event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	WAScene		*m_scene;
	HandleFrame *m_handleFrame;
	int m_handleBuffer;
	qreal m_grid;

	int counter;
	WAGroup * group;

};

#endif // WAVIEW_H
