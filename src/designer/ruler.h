/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2010 Shahazan Ali <KernelCoder>
   Copyright (C) 2019 Martin Reininger <nitramr>

   Widget based on code from https://kernelcoder.wordpress.com/2010/08/25/how-to-insert-ruler-scale-type-widget-into-a-qabstractscrollarea-type-widget/

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

#ifndef RULER_H
#define RULER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#define RULER_SIZE 20

class QDRuler : public QWidget
{
    Q_OBJECT
    Q_ENUMS(RulerType)
    Q_PROPERTY(qreal origin READ origin WRITE setOrigin)
    Q_PROPERTY(qreal scaleFactor READ scaleFactor WRITE setScaleFactor)
public:
    enum RulerType { Horizontal, Vertical };

    QDRuler(QDRuler::RulerType rulerType, QWidget* parent);

    QSize minimumSizeHint() const;

    QDRuler::RulerType rulerType() const;

    qreal origin() const;
    qreal scaleFactor() const;
    QColor markerColor() const;

public slots:

    void setOrigin(const qreal origin);
    void setCursorPos(const QPoint cursorPos);
    void setMouseTrack(const bool track);
    void setScaleFactor(qreal scaleFactor);
    void setMarkerColor(const QColor color);
    void setMarkerRange(qreal start, qreal stop);

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

private:
    void drawAScaleMeter(QPainter* painter, QRectF rulerRect, qreal scaleMeter, qreal startPositionLine, bool drawNumber = false);
    void drawFromOriginTo(QPainter* painter, QRectF rulerRect, qreal startMark, qreal endMark, int startTickNo, qreal step, qreal startPositionLine, bool drawNumber);
    void drawMousePosTick(QPainter* painter);
    void drawMarkerRange(QPainter* painter);

    RulerType m_RulerType;
    qreal m_Origin;
    QPoint m_CursorPos;
    bool m_MouseTracking;
    qreal m_scaleFactor;
    QColor m_color;
    qreal m_markerStart;
    qreal m_markerStop;
};

#endif // RULER_H
