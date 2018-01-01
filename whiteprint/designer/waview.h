#ifndef WAVIEW_H
#define WAVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class WAView : public QGraphicsView
{
    Q_OBJECT
public:
    WAView(QWidget * parent = 0);
    WAView(QGraphicsScene * scene, QWidget * parent = 0);

protected:
    void wheelEvent(QWheelEvent *event);


};

#endif // WAVIEW_H
