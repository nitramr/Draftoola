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

#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>

#include <itembase.h>
#include <artboard.h>

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CanvasScene(QObject *parent = nullptr);

    qreal scaleFactor() const;
    void setScaleFactor(qreal factor);

public slots:
    void exportItems();
    void exportItem(AbstractItemBase *item);

private:
    qreal m_scaleFactor;
    int m_grid;
    QPainterPath m_hoverPath;
    QPointF m_hoverPoint;
    QTransform m_hoverTransform;
    qreal m_hoverRotation;

    void saveImage(AbstractItemBase *bi, qreal multiplier, const QString outputPath, QColor bgColor = Qt::transparent);
    void saveSVG(AbstractItemBase *bi, const QString outputPath);
    void savePDF(AbstractItemBase *bi, const QString outputPath);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);
    void drawBackground(QPainter *painter, const QRectF &rect);
	void drawForeground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CANVASSCENE_H
