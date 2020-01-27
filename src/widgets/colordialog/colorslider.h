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

#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QWidget>

class ColorSlider : public QWidget
{
    Q_OBJECT
public:

    enum SliderType {
        Hue = 0,
        Alpha = 1
    };

    explicit ColorSlider(SliderType type, QWidget *parent = nullptr);
    ~ColorSlider() = default;

public slots:
    void setColor(QColor color, qreal alpha);
    void setColor(int hue, int saturation, int value, qreal alpha);

signals:
    void newColor(QColor,qreal);

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
    int m_maxValue;
    qreal m_alpha;
    SliderType m_type;

    QPoint colorPos();
    int colorVal(const QPoint &pt);
    void setColor(const QPoint &pt);

    QRect paintRect() const;

    void drawColorMap();

    QPixmap pix;

};

#endif // COLORSLIDER_H
