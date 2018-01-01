#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "handleframe.h"
#include "whiteprint/item/artboard.h"

class WAScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WAScene(QObject *parent = 0);

    // Properties
    void setScaleFactor(qreal factor);
    qreal scaleFactor() const;

private:
    HandleFrame *m_handleFrame;
    int m_handleBuffer;
	qreal m_grid;
    qreal m_scaleFactor;

protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent * e);

private slots:
    void updateHandleFrame();
    void updateItemProperties();

signals:
    void emitActiveItem(ItemBase * item);


};

#endif // WASCENE_H
