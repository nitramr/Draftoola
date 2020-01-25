#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

#include <canvasscene.h>
#include <handleframe.h>
#include <ruler.h>
#include <itemgroup.h>

class CanvasView : public QGraphicsView
{
    Q_OBJECT
public:
    CanvasView(QWidget * parent = nullptr);
    HandleFrame *handleFrame() const;

    void addItem(AbstractItemBase *item, qreal x = 0, qreal y = 0, AbstractItemBase *parent = nullptr);

    AbstractItemBase::RenderQuality renderQuality() const;
    void setRenderQuality(AbstractItemBase::RenderQuality renderQuality);

    AbstractItemBase *itemByName(const QString name);
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
    Artboard    *m_activeArtboard;
    QDRuler     *m_HRuler;
    QDRuler     *m_VRuler;

    AbstractItemBase::RenderQuality m_renderQuality;

    void applyScaleFactor();
    qreal scaleFactor() const;

    ItemGroup *createItemGroup(const QList<QGraphicsItem *> &items);
    QList<AbstractItemBase*> m_copyCache;

    Artboard *getTopLevelArtboard(QGraphicsItem *item);


signals:
    void signalViewIsDragged(bool);
    void itemsChanged();
    void zoomChanged(qreal);

public slots:
    void groupItems();
    void ungroupItems();
    void deleteItems();
    void copyItems(bool asDuplicate);
    void pasteItems();

private slots:
    void resetItemCache();
    void updateVRuler();
    void updateHRuler();
    void updateRulerMarker();
    void filterSelection(QRect viewportRect, QPointF fromScenePoint, QPointF toScenePoint);


};

#endif // CANVASVIEW_H
