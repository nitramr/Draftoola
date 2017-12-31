#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "whiteprint/item/handleframe.h"

class WAScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WAScene(QObject *parent = 0);


private:
    HandleFrame *m_handleFrame;
    int m_handleBuffer;
	qreal m_grid;

protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);

private slots:
    void updateHandleFrame();


};

#endif // WASCENE_H
