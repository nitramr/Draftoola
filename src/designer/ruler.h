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

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

private:
    void drawAScaleMeter(QPainter* painter, QRectF rulerRect, qreal scaleMeter, qreal startPositionLine, bool drawNumber = false);
    void drawFromOriginTo(QPainter* painter, QRectF rulerRect, qreal startMark, qreal endMark, int startTickNo, qreal step, qreal startPositionLine, bool drawNumber);
    void drawMousePosTick(QPainter* painter);

    RulerType m_RulerType;
    qreal m_Origin;
    QPoint m_CursorPos;
    bool m_MouseTracking;
    qreal m_scaleFactor;
    QColor m_color;
};

#endif // RULER_H
