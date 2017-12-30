#ifndef WASCENE_H
#define WASCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "whiteprint/item/handleframe.h"

class WAScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WAScene(QObject *parent = 0);

private:
    HandleFrame *m_handleFrame;
    int m_handleBuffer;

private slots:
    void updateHandleFrame();


};

#endif // WASCENE_H
