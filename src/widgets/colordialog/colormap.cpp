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

#include "colormap.h"

#include <QPainter>
#include <QDebug>
#include <qevent.h>

static int pWidth = 220;
static int pHeight = 180;
static int cSize = 16;

ColorMap::ColorMap(QWidget* parent)
    : QFrame(parent)
{
    m_hue = 0;
    m_saturation = 0;
    m_value = 0;
    m_alpha = 0.0;
    setColor(m_hue, m_saturation, m_value, m_alpha);

    setAttribute(Qt::WA_NoSystemBackground);
//    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed) );
}

/*!
 * \brief Return position of current color
 * \return
 */
QPoint ColorMap::colorPos()
{
    QRect r = contentsRect();
    return QPoint((0 + m_saturation) * (r.width() - 1) / 255, (255 - m_value) * (r.height() - 1) / 255);
}

int ColorMap::valPt(const QPoint &pt)
{
    QRect r = contentsRect();
    return 255 - pt.y() * 255 / (r.height() - 1);
}

int ColorMap::satPt(const QPoint &pt)
{
    QRect r = contentsRect();
    return 0 + pt.x() * 255 / (r.width() - 1);
}

/*!
 * \brief Set color of given point
 * \param pt
 */
void ColorMap::setColor(const QPoint &pt)
{
    setColor(m_hue, satPt(pt), valPt(pt), m_alpha);
}


/*!
 * \brief Draw color map
 */
void ColorMap::drawColorMap()
{
    int w = width() - frameWidth() * 2;
    int h = height() - frameWidth() * 2;
    QImage img(w, h, QImage::Format_RGB32);
    int x, y;
    uint *pixel = (uint *) img.scanLine(0);
    for (y = 0; y < h; y++) {
        const uint *end = pixel + w;
        x = 0;
        while (pixel < end) {
            QPoint p(x, y);
            QColor c;
            c.setHsv(m_hue, satPt(p), valPt(p));
            *pixel = c.rgb();
            ++pixel;
            ++x;
        }
    }
    pix = QPixmap::fromImage(img);

}


void ColorMap::setColor(QColor color, qreal alpha)
{
    setColor(color.hue(), color.saturation(), color.value(), alpha);
}

QSize ColorMap::sizeHint() const
{
    return QSize(pWidth + 2*frameWidth(), pHeight + 2*frameWidth());
}

void ColorMap::setColor(int hue, int saturation, int value, qreal alpha)
{
    int nhue = qMin(qMax(0,hue), 359);
    int nsat = qMin(qMax(0,saturation), 255);
    int nval = qMin(qMax(0,value), 255);
    if (nhue == m_hue && nsat == m_saturation && nval == m_value)
        return;

    if(nhue != m_hue){
        drawColorMap(); // repaint for hue
        repaint();
    }

    QRect r(colorPos(), QSize(cSize,cSize));
    m_hue = nhue;
    m_saturation = nsat;
    m_value = nval;
    m_alpha = alpha;
    r = r.united(QRect(colorPos(), QSize(cSize,cSize)));
    r.translate(contentsRect().x()-9, contentsRect().y()-9);

    repaint(r);
}

void ColorMap::mouseMoveEvent(QMouseEvent *m)
{
    QPoint p = m->pos() - contentsRect().topLeft();
    setColor(p);

    emit newColor(QColor::fromHsv(m_hue, m_saturation, m_value),
                  m_alpha);
}

void ColorMap::mousePressEvent(QMouseEvent *m)
{
    QPoint p = m->pos() - contentsRect().topLeft();
    setColor(p);

    emit newColor(QColor::fromHsv(m_hue, m_saturation, m_value),
                  m_alpha);
}

void ColorMap::paintEvent(QPaintEvent* )
{
    QPainter p(this);
    drawFrame(&p);
    QRect r = contentsRect();

    p.drawPixmap(r.topLeft(), pix);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPoint pt = colorPos() + r.topLeft();

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

void ColorMap::resizeEvent(QResizeEvent *ev)
{
    QFrame::resizeEvent(ev);
    drawColorMap();
}

