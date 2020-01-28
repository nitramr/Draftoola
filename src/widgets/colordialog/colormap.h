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

#ifndef COLORMAP_H
#define COLORMAP_H

#include <QFrame>
#include <color.h>

class ColorMap : public QFrame
{
    Q_OBJECT
public:
    ColorMap(QWidget* parent = nullptr);
    ~ColorMap() = default;

public slots:
    void setColor(Color color, qreal alpha);

signals:
    void newColor(Color color, qreal alpha);

protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    int m_hue;
    int m_saturation;
    int m_value;
    qreal m_alpha;
    Color m_color;

    QPoint colorPos();
    int satPt(const QPoint &pt);
    int valPt(const QPoint &pt);
    void setColor(const QPoint &pt);
    void setColor(int hue, int saturation, int m_value, qreal alpha);

    void drawColorMap();

    QPixmap pix;

};



#endif // COLORMAP_H
