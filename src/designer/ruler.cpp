/*
 *  Based on https://kernelcoder.wordpress.com/tag/ruler-in-qgraphicsview/
 *
 */

#include "ruler.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

QDRuler::QDRuler(QDRuler::RulerType rulerType, QWidget *parent): QWidget(parent),
    m_RulerType(rulerType), m_Origin(0.), m_MouseTracking(true), m_scaleFactor(1.), m_color(QColor())
{
    setMouseTracking(true);
    QFont txtFont(this->font());
    txtFont.setPixelSize(9);
    setFont(txtFont);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QSize QDRuler::minimumSizeHint() const
{
    return QSize(RULER_SIZE,RULER_SIZE);
}

QDRuler::RulerType QDRuler::rulerType() const
{
    return m_RulerType;
}

qreal QDRuler::origin() const
{
    return m_Origin;
}

qreal QDRuler::scaleFactor() const
{
    return m_scaleFactor;
}

QColor QDRuler::markerColor() const
{
    return m_color;
}

void QDRuler::setOrigin(const qreal origin)
{
    if (m_Origin != origin)
    {
        m_Origin = origin;
        update();
    }
}

void QDRuler::setCursorPos(const QPoint cursorPos)
{
    m_CursorPos = this->mapFromGlobal(cursorPos);
    update();
}

void QDRuler::setMouseTrack(const bool track)
{
    if (m_MouseTracking != track)
    {
        m_MouseTracking = track;
        update();
    }
}

void QDRuler::setScaleFactor(qreal scaleFactor)
{
    if (m_scaleFactor != scaleFactor)
    {
        m_scaleFactor = scaleFactor;
        update();
    }
}

void QDRuler::setMarkerColor(const QColor color)
{
    if (m_color != color)
    {
        m_color = color;
        update();
    }
}

/***************************************************
 *
 * Events
 *
 ***************************************************/

void QDRuler::mouseMoveEvent(QMouseEvent *event)
{
    m_CursorPos = event->pos();
    update();
    QWidget::mouseMoveEvent(event);
}

void QDRuler::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    QRectF rulerRect = this->rect();

    // at first fill the rect
    painter.fillRect(rulerRect,QColor(255,255,255));


    if(scaleFactor() >=8){
        drawAScaleMeter(&painter,rulerRect,1,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/1.5);
        drawAScaleMeter(&painter,rulerRect,5,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/2);
        drawAScaleMeter(&painter,rulerRect,10,0, true);
    }

    if(scaleFactor() >=4 && scaleFactor() < 8){
        drawAScaleMeter(&painter,rulerRect,1,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/1.5);
        drawAScaleMeter(&painter,rulerRect,10,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/2);
        drawAScaleMeter(&painter,rulerRect,20,0, true);
    }

    if(scaleFactor() >=1 && scaleFactor() < 4){
        drawAScaleMeter(&painter,rulerRect,4,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/1.5);
        drawAScaleMeter(&painter,rulerRect,20,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/2);
        drawAScaleMeter(&painter,rulerRect,40,0, true);
    }

    if(scaleFactor() >=0.4 && scaleFactor() < 1){
        drawAScaleMeter(&painter,rulerRect,8,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/1.5);
        drawAScaleMeter(&painter,rulerRect,40,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/2);
        drawAScaleMeter(&painter,rulerRect,80,0, true);
    }

    if(scaleFactor() >=0.2 && scaleFactor() < 0.4){
        drawAScaleMeter(&painter,rulerRect,80,(Horizontal == m_RulerType ? rulerRect.height() : rulerRect.width())/2);
        drawAScaleMeter(&painter,rulerRect,160,0, true);
    }

    if(scaleFactor() < 0.2){
        drawAScaleMeter(&painter,rulerRect,320,0, true);
    }



    // drawing the current mouse position indicator
    drawMousePosTick(&painter);

    // drawing no man's land between the ruler & view
    QPointF starPt = Horizontal == m_RulerType ? rulerRect.bottomLeft()
                                               : rulerRect.topRight();
    QPointF endPt = Horizontal == m_RulerType ? rulerRect.bottomRight()
                                              : rulerRect.bottomRight();
    painter.setPen(QPen(Qt::gray,2));
    painter.drawLine(starPt,endPt);
}

/***************************************************
 *
 * Helper
 *
 ***************************************************/

void QDRuler::drawAScaleMeter(QPainter *painter, QRectF rulerRect, qreal scaleMeter, qreal startPositionLine, bool drawNumber)
{
    // Flagging whether we are horizontal or vertical only to reduce
    // to cheching many times
    bool isHorzRuler = Horizontal == m_RulerType;

    qreal rulerStartMark = isHorzRuler ? rulerRect.left() : rulerRect.top();
    qreal rulerEndMark = isHorzRuler ? rulerRect.right() : rulerRect.bottom();

    qreal m_OriginOffset = m_Origin;
    m_OriginOffset *= m_scaleFactor;
    scaleMeter *= m_scaleFactor;

    // Condition A # If origin point is between the start & end mark,
    // we have to draw both from origin to left mark & origin to right mark.
    // Condition B # If origin point is left of the start mark, we have to draw
    // from origin to end mark.
    // Condition C # If origin point is right of the end mark, we have to draw
    // from origin to start mark.
    if (m_OriginOffset >= rulerStartMark && m_OriginOffset <= rulerEndMark)
    {
        drawFromOriginTo(painter, rulerRect, m_OriginOffset, rulerEndMark, 0, scaleMeter, startPositionLine, drawNumber);
        drawFromOriginTo(painter, rulerRect, m_OriginOffset, rulerStartMark, 0, -scaleMeter, startPositionLine, drawNumber);
    }
    else if (m_OriginOffset < rulerStartMark)
    {
        int tickNo = int((rulerStartMark - m_OriginOffset ) / scaleMeter);
        drawFromOriginTo(painter, rulerRect, m_OriginOffset + scaleMeter * tickNo,
                         rulerEndMark, tickNo, scaleMeter, startPositionLine, drawNumber);
    }
    else if (m_OriginOffset > rulerEndMark)
    {
        int tickNo = int((m_OriginOffset - rulerEndMark) / scaleMeter);
        drawFromOriginTo(painter, rulerRect, m_OriginOffset - scaleMeter * tickNo,
                         rulerStartMark, tickNo, -scaleMeter, startPositionLine, drawNumber);
    }

}

void QDRuler::drawFromOriginTo(QPainter *painter, QRectF rulerRect, qreal startMark, qreal endMark, int startTickNo, qreal step, qreal startPositionLine, bool drawNumber)
{
    bool isHorzRuler = Horizontal == m_RulerType;

    for (qreal current = startMark; (step < 0 ? current  >= endMark : current <= endMark); current += step)
    {
        qreal x1 = isHorzRuler ? current : rulerRect.left() + startPositionLine;
        qreal y1 = isHorzRuler ? rulerRect.top() + startPositionLine : current;
        qreal x2 = isHorzRuler ? current : rulerRect.right();
        qreal y2 = isHorzRuler ? rulerRect.bottom() : current;

        painter->setPen(Qt::gray);
        painter->drawLine(QLineF(x1,y1,x2,y2));


        if (drawNumber)
        {

            painter->setPen(Qt::black);

            //           painter->drawText(QPointF(x1 + 1, y1 + (isHorzRuler ? 7 : -2)), QString::number(int(step/m_scaleFactor) * startTickNo++) );

            if(isHorzRuler){
                painter->drawText(QPointF(current + 2, (isHorzRuler ? 8 : -1)), QString::number(int(step/m_scaleFactor) * startTickNo++) );

            }else{
                painter->save();
                painter->rotate(90);
                painter->drawText(QPointF(current + 2, (isHorzRuler ? 8 : -1)), QString::number(int(step/m_scaleFactor) * startTickNo++) );
                painter->restore();
            }

        }
    }
}

void QDRuler::drawMousePosTick(QPainter *painter)
{
    if (m_MouseTracking)
    {
        QPoint starPt = m_CursorPos;
        QPoint endPt;
        if (Horizontal == m_RulerType)
        {
            starPt.setY(this->rect().top());
            endPt.setX(starPt.x());
            endPt.setY(this->rect().bottom());
        }
        else
        {
            starPt.setX(this->rect().left());
            endPt.setX(this->rect().right());
            endPt.setY(starPt.y());
        }
        painter->setPen(QPen(m_color));
        painter->drawLine(starPt,endPt);
    }
}
