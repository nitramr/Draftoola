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

#include <gradienteditor.h>
#include "tabgradient.h"
#include "ui_tabgradient.h"

#include <gradient.h>

TabGradient::TabGradient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabGradient)
{
    ui->setupUi(this);


    QLinearGradient linear(0,1,100,1);
    linear.setColorAt(0.0, Qt::black);
    linear.setColorAt(0.5, Qt::white);
    linear.setColorAt(1.0, QColor(255,0,0,128));

    Gradient gradient("Gradient", linear);

    GradientEditor *slider = new GradientEditor();
    slider->setGradient(gradient);


    ui->verticalLayout->addWidget(slider);
}

TabGradient::~TabGradient()
{
    delete ui;
}
