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

    m_colorMap = new ColorMap();
    m_colorSlider = new ColorSlider(ColorSlider::Hue);
    m_alphaSlider = new ColorSlider(ColorSlider::Alpha);

    ui->sectionColorMap->setText(tr("Color Map"));
    ui->sectionColorMap->addWidget(m_colorMap);
    ui->sectionColorMap->addWidget(m_colorSlider);
    ui->sectionColorMap->addWidget(m_alphaSlider);

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

qreal TabColor::alpha() const
{
    return m_alpha;
}

void TabColor::connectSlots()
{
    connect(ui->colorInput, &ColorInput::colorChanged, this, &TabColor::updateColor);
    connect(m_colorMap, &ColorMap::newColor, this, &TabColor::updateColor);
    connect(m_colorSlider, &ColorSlider::newColor, this, &TabColor::updateColor);
    connect(m_alphaSlider, &ColorSlider::newColor, this, &TabColor::updateColor);
}


void TabColor::disconnectSlots()
{
    disconnect(ui->colorInput, &ColorInput::colorChanged, this, &TabColor::updateColor);
    disconnect(m_colorMap, &ColorMap::newColor, this, &TabColor::updateColor);
    disconnect(m_colorSlider, &ColorSlider::newColor, this, &TabColor::updateColor);
    disconnect(m_alphaSlider, &ColorSlider::newColor, this, &TabColor::updateColor);
}

void TabColor::setColor(Color color, qreal alpha)
{
    m_color = color;
    m_alpha = alpha;

    disconnectSlots();

    ui->colorInput->setColor(m_color, m_alpha);
    m_colorMap->setColor(m_color, m_alpha);
    m_colorSlider->setColor(m_color, m_alpha);
    m_alphaSlider->setColor(m_color, m_alpha);

    connectSlots();

}

void TabColor::updateColor(Color color, qreal alpha)
{
    setColor(color, alpha);

    emit colorChanged();
}
