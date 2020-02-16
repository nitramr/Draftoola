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

#include "tabcolors.h"
#include "ui_tabcolors.h"

#include <QDebug>
#include <utilities.h>

TabColors::TabColors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabColors)
{
    ui->setupUi(this);

    m_colorMap2D = new color_widgets::Color2DSlider();

    ui->sectionColorMap->setText(tr("Color Picker"));
    ui->sectionColorMap->addWidget(m_colorMap2D);

    ui->sectionColorPalette->setText(tr("Color Palette"));

    QBrush checkPattern( paintGrid() );
    ui->gradientEditor->setBackground( checkPattern );
    ui->alphaSlider->setBackground( checkPattern );
    ui->alphaSlider->setRange(0,100);
    ui->preview->setBackground( checkPattern );
    ui->preview->setDisplayMode(color_widgets::ColorPreview::DisplayMode::SplitAlpha);
    ui->preview->setOrientation(Qt::Vertical);

    connectSlots();
}

TabColors::~TabColors()
{
    delete ui;
}

Color TabColors::color() const
{
    return m_color;
}

Gradient TabColors::gradient() const
{
    return m_gradient;
}

void TabColors::enableGradientControls(bool enabled)
{

    ui->gradientEditor->setVisible(enabled);

}



void TabColors::connectSlots()
{
    connect(ui->colorInput, &ColorInput::colorChanged, this, &TabColors::updateColor);
    connect(m_colorMap2D, &color_widgets::Color2DSlider::colorChanged, this, &TabColors::updateColor);
    connect(ui->hueSlider, &color_widgets::HueSlider::colorHueChanged, this, &TabColors::updateHue);
    connect(ui->alphaSlider, &color_widgets::GradientSlider::valueChanged, this, &TabColors::updateAlpha);

    connect(ui->gradientEditor, &color_widgets::GradientEditor::stopsChanged, this, &TabColors::updateGradient);
    connect(ui->gradientEditor, &color_widgets::GradientEditor::selectedStopChanged, this, &TabColors::updateGradientStop);
}


void TabColors::disconnectSlots()
{
    disconnect(ui->colorInput, &ColorInput::colorChanged, this, &TabColors::updateColor);
    disconnect(m_colorMap2D, &color_widgets::Color2DSlider::colorChanged, this, &TabColors::updateColor);
    disconnect(ui->hueSlider, &color_widgets::HueSlider::colorHueChanged, this, &TabColors::updateHue);
    disconnect(ui->alphaSlider, &color_widgets::GradientSlider::valueChanged, this, &TabColors::updateAlpha);

    disconnect(ui->gradientEditor, &color_widgets::GradientEditor::stopsChanged, this, &TabColors::updateGradient);
    disconnect(ui->gradientEditor, &color_widgets::GradientEditor::selectedStopChanged, this, &TabColors::updateGradientStop);
}

void TabColors::setColor(Color color)
{    
    m_color = color;

    disconnectSlots();

    ui->colorInput->setColor(m_color);
    m_colorMap2D->setColor(m_color);
    ui->hueSlider->setColorHue(m_color.hueF());
    ui->hueSlider->setColorAlpha(m_color.alphaF());
    ui->alphaSlider->setFirstColor(QColor::fromRgb(m_color.red(), m_color.green(), m_color.blue(), 0));
    ui->alphaSlider->setLastColor(QColor::fromRgb(m_color.red(), m_color.green(), m_color.blue(), 255));
    ui->alphaSlider->setValue(qRound( m_color.alphaF() * 100) );
    ui->preview->setColor(m_color);

    ui->gradientEditor->setSelectedColor(m_color);

    connectSlots();

}

void TabColors::setGradient(Gradient gradient)
{
    m_gradient = gradient;

    disconnectSlots();
    ui->gradientEditor->setGradient(m_gradient.linear());
    ui->gradientEditor->setSelectedStop(0);
    setColor(ui->gradientEditor->selectedColor());
    connectSlots();

}

void TabColors::updateHue(qreal hue)
{
    updateColor( QColor::fromHsvF(hue, m_color.saturationF(),m_color.valueF(), ui->hueSlider->colorAlpha()) );
}


void TabColors::updateAlpha(int alpha)
{
    m_color.setAlphaF(alpha / 100.0);
    updateColor(m_color);
}

void TabColors::updateGradientStop(int stop)
{
    updateColor(ui->gradientEditor->selectedColor());
}

void TabColors::updateGradient(QGradientStops stops)
{
    m_gradient.setStops(stops);
    emit gradientChanged();
}

void TabColors::updateColor(Color color)
{
    setColor(color);
    emit colorChanged();

    // update gradient if color changed
    updateGradient(ui->gradientEditor->stops());
}


