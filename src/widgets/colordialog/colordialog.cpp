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

#include "colordialog.h"
#include "ui_colordialog.h"

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

ColorDialog::ColorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);

    m_mode = Mode::FillLayout;
    m_fillType = FillType::Color;

    m_opacity = -1.0;

    connect(ui->tabColor, &TabColor::colorChanged, this, &ColorDialog::updateProperty);

}

ColorDialog::~ColorDialog()
{
    delete ui;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

/*!
 * \brief Return layout mode of color dialog
 */
ColorDialog::Mode ColorDialog::mode() const
{
    return m_mode;
}

Gradient ColorDialog::gradient() const
{
    return m_gradient;
}

Color ColorDialog::color() const
{
    return m_color;
}

QPixmap ColorDialog::pixmap() const
{
    return m_pixmap;
}

qreal ColorDialog::opacity() const
{
    return m_opacity;
}

FillType ColorDialog::fillType() const
{
    return m_fillType;
}

void ColorDialog::setProperty(AbstractItemProperty *property)
{
    if(!property) return;

    switch(property->type()){
    // Fill ****************************************************
    case AbstractItemProperty::Fill:{

        Fills *prop = static_cast<Fills*>(property);

        if(prop){

            m_fillType = prop->fillType();
            m_pixmap = prop->pixmap();
            m_gradient = prop->gradient();
            m_color = prop->color();
            m_opacity = prop->opacity();

            ui->tabColor->setColor(m_color, m_opacity);

            m_mode = Mode::FillLayout;
        }

        break;
    }

        // Stroke ****************************************************
    case AbstractItemProperty::Stroke:{

        Stroke *prop = static_cast<Stroke*>(property);

        if(prop){

            m_fillType = prop->fillType();
            m_gradient = prop->gradient();
            m_color = prop->color();
            m_opacity = m_color.alphaF();

            ui->tabColor->setColor(m_color, m_opacity);

            m_mode = Mode::StrokeLayout;
        }

        break;
    }

        // Shadow ****************************************************
    case AbstractItemProperty::Shadow:{

        Shadow *prop = static_cast<Shadow*>(property);

        if(prop){

            m_color = prop->color();
            m_opacity = m_color.alphaF();

            ui->tabColor->setColor(m_color, m_opacity);

            m_mode = Mode::ShadowLayout;
        }
        break;
    }
    }

    configurateDialog();

}

/*!
 * \brief Configure color dialog based on mode
 */
void ColorDialog::configurateDialog()
{
    //TODO: use m_mode
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

/*!
 * \brief [SLOT] Update loaded property with new data from color dialog.
 */
void ColorDialog::updateProperty()
{
    m_color = ui->tabColor->color();
    m_opacity = ui->tabColor->alpha();

    emit propertyChanged();
}
