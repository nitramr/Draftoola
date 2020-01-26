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


FillType ColorDialog::fillType()
{
    return m_fillType;
}



/*!
 * \brief Return layout mode of color dialog
 */
ColorDialog::Mode ColorDialog::mode() const
{
    return m_mode;
}


void ColorDialog::setProperty(AbstractItemProperty *property)
{
     if(!property) return;

    m_property = property;

    switch(m_property->type()){
    case AbstractItemProperty::Fill:{
        // Fill ****************************************************
        Fills *fill = static_cast<Fills*>(m_property);

        if(fill){

            ui->tabColor->setColor(fill->color(), fill->opacity());

//            m_fillType = fill->fillType();

//            switch(fill->fillType()){
//            case FillType::Color:
//                ui->tabColor->setColor(fill->color(), fill->opacity());
//                break;
//            case FillType::Image:
//                break;
//            case FillType::LinearGradient:
//                break;
//            case FillType::RadialGradient:
//                break;
//            case FillType::ConicalGradient:
//                break;
//            case FillType::Pattern:
//                break;
//            }

            m_mode = Mode::FillLayout;
        }

        break;
    }
    case AbstractItemProperty::Stroke:{
        // Stroke ****************************************************
        Stroke *stroke = static_cast<Stroke*>(m_property);

        if(stroke){

            ui->tabColor->setColor(stroke->color(), stroke->color().alphaF());
            m_mode = Mode::StrokeLayout;
        }

        break;
    }
    case AbstractItemProperty::Shadow:{
        // Shadow ****************************************************
        Shadow *shadow = static_cast<Shadow*>(m_property);

        if(shadow){

            ui->tabColor->setColor(shadow->color(), shadow->color().alphaF());
            m_mode = Mode::ShadowLayout;
        }
        break;
    }
    }

}

Fills *ColorDialog::fill()
{
    Fills *prop = static_cast<Fills*>(m_property);
    return (prop) ? prop : new Fills();
}

Stroke *ColorDialog::stroke()
{
    Stroke *prop = static_cast<Stroke*>(m_property);
    return (prop) ? prop : new Stroke();
}

Shadow *ColorDialog::shadow()
{
    Shadow *prop = static_cast<Shadow*>(m_property);
    return (prop) ? prop : new Shadow();
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
    if(!m_property) return;

    switch(m_property->type()){
    case AbstractItemProperty::Fill:{
        Fills *property = static_cast<Fills*>(m_property);

        switch(property->fillType()){
        case FillType::Color:
            property->setColor( ui->tabColor->color() );
            property->setOpacity( ui->tabColor->alpha() );
            break;
        default:

            break;
        }

        break;
    }
    case AbstractItemProperty::Stroke:{
        Stroke *property = static_cast<Stroke*>(m_property);

        QColor color = ui->tabColor->color();
        color.setAlphaF( ui->tabColor->alpha() );
        property->setColor( color );

        break;
    }
    case AbstractItemProperty::Shadow:{

        Shadow *property = static_cast<Shadow*>(m_property);

        QColor color = ui->tabColor->color();
        color.setAlphaF( ui->tabColor->alpha() );
        property->setColor( color );

        break;
    }
    }

    emit propertyChanged();
}
