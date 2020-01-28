/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

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
    HandleFrame *handleFrame();

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
    void updateVRulerPosition();
    void updateHRulerPosition();
    void setRulerToSelection();
    void filterSelection(QRect viewportRect, QPointF fromScenePoint, QPointF toScenePoint);


};

#endif // CANVASVIEW_H
