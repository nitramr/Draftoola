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

#include "tabcolor.h"
#include "ui_tabcolor.h"

#include <QDebug>

TabColor::TabColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabColor)
{
    ui->setupUi(this);

    m_colorMap2D = new color_widgets::Color2DSlider();
    m_hueSlider = new color_widgets::HueSlider();
    m_alphaSlider2 = new color_widgets::GradientSlider();
    m_alphaSlider2->setRange(0,100);

    ui->sectionColorMap->setText(tr("Color Picker"));
    ui->sectionColorMap->addWidget(m_colorMap2D);
    ui->sectionColorMap->addWidget(m_hueSlider);
    ui->sectionColorMap->addWidget(m_alphaSlider2);

    ui->sectionColorPalette->setText(tr("Color Palette"));

    connectSlots();
}

TabColor::~TabColor()
{
    delete ui;
}

Color TabColor::color() const
{
    return m_color;
}


void TabColor::connectSlots()
{
    connect(ui->colorInput, &ColorInput::colorChanged, this, &TabColor::updateColor);
    connect(ui->colorInput, &ColorInput::alphaChanged, this, &TabColor::updateAlpha);
    connect(m_colorMap2D, &color_widgets::Color2DSlider::colorChanged, this, &TabColor::updateColor);
    connect(m_hueSlider, &color_widgets::HueSlider::colorHueChanged, this, &TabColor::updateHue);
    connect(m_alphaSlider2, &color_widgets::GradientSlider::valueChanged, this, &TabColor::updateAlpha);
}


void TabColor::disconnectSlots()
{
    disconnect(ui->colorInput, &ColorInput::colorChanged, this, &TabColor::updateColor);
    disconnect(ui->colorInput, &ColorInput::alphaChanged, this, &TabColor::updateAlpha);
    disconnect(m_colorMap2D, &color_widgets::Color2DSlider::colorChanged, this, &TabColor::updateColor);
    disconnect(m_hueSlider, &color_widgets::HueSlider::colorHueChanged, this, &TabColor::updateHue);
    disconnect(m_alphaSlider2, &color_widgets::GradientSlider::valueChanged, this, &TabColor::updateAlpha);
}

void TabColor::setColor(Color color)
{    
    m_color = color;

    qDebug() << m_color.alphaF();

    disconnectSlots();

    int alpha = qRound(m_color.alphaF() * 100);

    ui->colorInput->setColor(m_color, alpha);
    m_colorMap2D->setColor(m_color);
    m_hueSlider->setColorHue(m_color.hueF());
    m_alphaSlider2->setFirstColor(QColor::fromRgb(m_color.red(), m_color.green(), m_color.blue(), 0));
    m_alphaSlider2->setLastColor(QColor::fromRgb(m_color.red(), m_color.green(), m_color.blue(), 255));
    m_alphaSlider2->setValue(alpha);

    connectSlots();

}

void TabColor::updateHue(qreal hue)
{
    updateColor(QColor::fromHsvF(hue, m_color.saturationF(), m_color.valueF()));
}

void TabColor::updateColor(Color color)
{
    setColor(color);

    emit colorChanged();
}

void TabColor::updateAlpha(int alpha)
{
    m_color.setAlphaF(alpha / 100.0);

    setColor(m_color);

    emit colorChanged();
}
