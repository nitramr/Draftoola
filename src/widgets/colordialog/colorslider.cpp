/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2012 The Qt Company Ltd. - http://www.qt-project.org/
   Copyright (C) 2020 Martin Reininger <nitramr>

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

   Widget based on code of QColorDialog widget.

**************************************************************************************/

#include "colorslider.h"

#include <QPainter>
#include <QDebug>
#include <qevent.h>
#include <utilities.h>

static int pWidth = 220;
static int pHeight = 16;
static int cSize = 16;
static int barWidth = 6;

ColorSlider::ColorSlider(SliderType type, QWidget* parent)
    : QWidget(parent)
{
    m_type = type;
    m_hue = 0;
    m_saturation = 0;
    m_value = 0;
    m_alpha = 0.0;

    switch (m_type) {
    case SliderType::Hue:
        m_maxValue = 360;
        break;
    case SliderType::Alpha:
        m_maxValue = 100;
        break;
    }

    setColor(m_hue, m_saturation, m_value, m_alpha);

    setAttribute(Qt::WA_NoSystemBackground);
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed) );
}


/*!
 * \brief Return position of current color
 * \return
 */
QPoint ColorSlider::colorPos()
{
    QRect r = contentsRect();
    switch (m_type) {
    case SliderType::Hue:
        return QPoint((m_hue) * (r.width() - 1) / m_maxValue, pHeight/2);
        break;
    case SliderType::Alpha:
        return QPoint((m_alpha * 100.0) * (r.width() - 1) / m_maxValue, pHeight/2);
        break;
    }

    return QPoint();
}


int ColorSlider::colorVal(const QPoint &pt)
{
    QRect r = contentsRect();
    return pt.x() * m_maxValue / (r.width() - 1);
}

/*!
 * \brief Set color of given point
 * \param pt
 */
void ColorSlider::setColor(const QPoint &pt)
{
    switch (m_type) {
    case SliderType::Hue:
        setColor(colorVal(pt), m_saturation, m_value, m_alpha);
        break;
    case SliderType::Alpha:
        setColor(m_hue, m_saturation, m_value, colorVal(pt) / 100.0);
        break;
    }
}


/*!
 * \brief Draw color map
 */
void ColorSlider::drawColorMap()
{
    int w = width();
    int h = barWidth;
    QImage img(w, h, QImage::Format_ARGB32);
    int x, y;
    uint *pixel = (uint *) img.scanLine(0);

    for (y = 0; y < h; y++) {
        const uint *end = pixel + w;
        x = 0;
        while (pixel < end) {
            QPoint p(x, y);
            QColor c;

            switch (m_type) {
            case SliderType::Hue:
                c.setHsv(colorVal(p), 255, 255);
                break;
            case SliderType::Alpha:
                c.setHsv(m_hue, m_saturation, m_value, colorVal(p) * 2.55);
                break;
            }

            *pixel = c.rgba();
            ++pixel;
            ++x;
        }
    }

    pix = QPixmap::fromImage(img);

}


void ColorSlider::setColor(QColor color, qreal alpha)
{
    setColor(color.hue(), color.saturation(), color.value(), alpha);
}

QSize ColorSlider::sizeHint() const
{
    return QSize(pWidth, pHeight);
}

void ColorSlider::setColor(int hue, int saturation, int value, qreal alpha)
{
    int nhue = qMin(qMax(0,hue), 359);
    int nsat = qMin(qMax(0,saturation), 255);
    int nval = qMin(qMax(0,value), 255);
    qreal nalpha = qMin(qMax(0.0, alpha), 1.0);
    if(nhue == m_hue && nsat == m_saturation && nval == m_value && nalpha == m_alpha)
        return;

    if(m_type == Alpha && (nhue != m_hue || nsat != m_saturation || nval != m_value || nalpha != m_alpha) ){
        drawColorMap();
        repaint();
    }

    QRect r(colorPos(), QSize(cSize,cSize));
    m_hue = nhue;
    m_saturation = saturation;
    m_value = value;
    m_alpha = nalpha;
    r = r.united(QRect(colorPos(), QSize(cSize,cSize)));
    r.translate(contentsRect().x()-cSize/2, contentsRect().y()-cSize/2);

    repaint(r);
}



void ColorSlider::mouseMoveEvent(QMouseEvent *m)
{
    QPoint p = m->pos() - contentsRect().topLeft();
    setColor(p);

    emit newColor(QColor::fromHsv(m_hue, m_saturation, m_value),
                  m_alpha);
}

void ColorSlider::mousePressEvent(QMouseEvent *m)
{
    QPoint p = m->pos() - contentsRect().topLeft();
    setColor(p);

    emit newColor(QColor::fromHsv(m_hue, m_saturation, m_value),
                  m_alpha);
}

void ColorSlider::paintEvent(QPaintEvent* )
{
    QPainter p(this);
    p.setPen(Qt::NoPen);

    QPoint sliderPt( contentsRect().topLeft() + QPoint(0, (height() - barWidth) / 2));
    QRect r = pix.rect();
    r.translate(sliderPt);

    // Draw grid
    if(m_type == Alpha){
        paintGrid(p, r, QSize(6,3));
    }

    p.drawPixmap(sliderPt, pix);


    // Draw Cursor
    p.setRenderHint(QPainter::Antialiasing, true);
    QPoint pt = colorPos();

    QRect cursor(pt - QPoint(cSize/2, cSize/2), QSize(cSize, cSize));
    QPen pen(Qt::darkGray);
    pen.setWidth(4);
    p.setPen(pen);
    p.drawEllipse(cursor.adjusted(4,4,-4,-4));

    pen.setColor(Qt::white);
    pen.setWidth(2);
    p.setPen(pen);
    p.drawEllipse(cursor.adjusted(4,4,-4,-4));

}

void ColorSlider::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    drawColorMap();
}
