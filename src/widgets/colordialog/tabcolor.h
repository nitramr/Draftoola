/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

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

**************************************************************************************/

#ifndef TABSOLID_H
#define TABSOLID_H

#include <QWidget>

#include <color.h>
#include <colormap.h>
#include <colorslider.h>
#include <color_2d_slider.hpp>
#include <hue_slider.hpp>

namespace Ui {
class TabColor;
}

class TabColor : public QWidget
{
    Q_OBJECT

public:
    explicit TabColor(QWidget *parent = nullptr);
    ~TabColor();

    Color color() const;

private:
    Ui::TabColor *ui;

    color_widgets::Color2DSlider * m_colorMap2D;
    color_widgets::HueSlider * m_hueSlider;
    color_widgets::GradientSlider * m_alphaSlider2;
    Color m_color;

    void connectSlots();
    void disconnectSlots();

public slots:

    void setColor(Color color);

private slots:
    void updateHue(qreal hue);
    void updateColor(Color color);
    void updateAlpha(int alpha);

signals:
    void colorChanged();

};

#endif // TABSOLID_H
