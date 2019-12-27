#ifndef WAVIEW_H
#define WAVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

#include "canvasscene.h"
#include "handleframe.h"
#include "ruler.h"

class CanvasView : public QGraphicsView
{
    Q_OBJECT
public:
    CanvasView(/*WAScene *scene, */QWidget * parent = nullptr);
	HandleFrame *handleFrame() const;

    void addItem(AbstractItemBase *item, qreal x = 0, qreal y = 0, AbstractItemBase *parent = nullptr);

    QList<Artboard *> artboardList();

protected:
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent * event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
    CanvasScene	*m_scene;
	HandleFrame *m_handleFrame;
    int          m_handleBuffer;
    qreal        m_grid;
    QTimer      *timer;

    QList<Artboard*> m_artboardList;
    QDRuler                 *m_HRuler;
    QDRuler                 *m_VRuler;

    void applyScaleFactor();
    qreal scaleFactor() const;

signals:
    void signalViewIsDragged(bool);
    void itemsChanged();
    void signalScaleFactor(qreal);

private slots:
    void resetItemCache();
    void updateVRuler();
    void updateHRuler();

};

#endif // WAVIEW_H
