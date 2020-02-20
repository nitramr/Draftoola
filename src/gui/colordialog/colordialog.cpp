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

#include <QTabBar>
#include <QToolBar>

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


    // set tab data
    QString tabStyle = "QTabBar::tab { align: center; text-align: center; }";

    m_tabBar = new QTabBar();
    m_tabBar->setIconSize(QSize(24,24));
//    m_tabBar->setStyleSheet(tabStyle);
    m_tabBar->setExpanding(false);

    m_tabBar->addTab(QIcon(":icons/dark/colordialog/color.svg"), QString());
    m_tabBar->setTabData(0, QVariant::fromValue(FillType::Color));

    m_tabBar->addTab(QIcon(":icons/dark/colordialog/linear_gradient.png"), QString());
    m_tabBar->setTabData(1, QVariant::fromValue(FillType::LinearGradient));

    m_tabBar->addTab(QIcon(":icons/dark/colordialog/radial_gradient.png"), QString());
    m_tabBar->setTabData(2, QVariant::fromValue(FillType::RadialGradient));

    m_tabBar->addTab(QIcon(":icons/dark/colordialog/conical_gradient.png"), QString());
    m_tabBar->setTabData(3, QVariant::fromValue(FillType::ConicalGradient));

    m_tabBar->addTab(QIcon(":icons/dark/colordialog/image.svg"), QString());
    m_tabBar->setTabData(4, QVariant::fromValue(FillType::Image));

    ui->verticalLayout->insertWidget(0,m_tabBar);
    ui->tabColor->enableGradientControls(false);

    connect(m_tabBar, &QTabBar::currentChanged, this, &ColorDialog::changeTabs);
    connect(ui->tabColor, &TabColors::colorChanged, this, &ColorDialog::updateProperty);
    connect(ui->tabGradient, &TabColors::gradientChanged, this, &ColorDialog::updateProperty);
    connect(ui->tabImage, &TabImage::imageChanged, this, &ColorDialog::updateProperty);

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

QString ColorDialog::imagePath() const
{
    return m_imagePath;
}

qreal ColorDialog::opacity() const
{
    return m_opacity;
}

FillType ColorDialog::fillType() const
{
    return m_fillType;
}

Fills::FillMode ColorDialog::fillMode() const
{
    return m_fillMode;
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
            m_imagePath = prop->imagePath();
            m_gradient = prop->gradient();
            m_color = prop->color();
            m_opacity = prop->opacity();
            m_fillMode = prop->fillMode();

            ui->tabColor->setColor(m_color);
            ui->tabGradient->setGradient(m_gradient);
            ui->tabImage->setImagePath(m_imagePath);
            ui->tabImage->setFillMode(m_fillMode);

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

            ui->tabColor->setColor(m_color);
            ui->tabGradient->setGradient(m_gradient);

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

            ui->tabColor->setColor(m_color);
            ui->tabGradient->setGradient(m_gradient);

            m_mode = Mode::ShadowLayout;
        }
        break;
    }
    }

    configurateDialog();
    selectTab();

}

/*!
 * \brief Configure color dialog based on mode
 */
void ColorDialog::configurateDialog()
{
    switch(m_mode){
    case Mode::FillLayout:

        m_tabBar->setTabEnabled(0, true);
        m_tabBar->setTabEnabled(1, true);
        m_tabBar->setTabEnabled(2, true);
        m_tabBar->setTabEnabled(3, true);
        m_tabBar->setTabEnabled(4, true);

        break;
    case Mode::StrokeLayout:
        m_tabBar->setTabEnabled(0, true);
        m_tabBar->setTabEnabled(1, true);
        m_tabBar->setTabEnabled(2, true);
        m_tabBar->setTabEnabled(3, true);
        m_tabBar->setTabEnabled(4, false);

        break;
    case Mode::ShadowLayout:
        m_tabBar->setTabEnabled(0, true);
        m_tabBar->setTabEnabled(1, false);
        m_tabBar->setTabEnabled(2, false);
        m_tabBar->setTabEnabled(3, false);
        m_tabBar->setTabEnabled(4, false);

        break;
    }

}

void ColorDialog::selectTab()
{
    switch (m_fillType) {
    default:
    case FillType::Color:
       m_tabBar->setCurrentIndex(0);
       ui->tabs->setCurrentIndex(0);
        break;
    case FillType::LinearGradient:
       m_tabBar->setCurrentIndex(1);
       ui->tabs->setCurrentIndex(1);
        break;
    case FillType::RadialGradient:
        m_tabBar->setCurrentIndex(2);
        ui->tabs->setCurrentIndex(1);
        break;
    case FillType::ConicalGradient:
        m_tabBar->setCurrentIndex(3);
        ui->tabs->setCurrentIndex(1);
        break;
    case FillType::Image:
       m_tabBar->setCurrentIndex(4);
       ui->tabs->setCurrentIndex(2);
        break;
    case FillType::Pattern:
        break;
    }

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
    m_gradient = ui->tabGradient->gradient();
    m_imagePath = ui->tabImage->imagePath();
    m_fillMode = ui->tabImage->fillMode();

    emit propertyChanged();
}

void ColorDialog::changeTabs(int index)
{
    m_fillType = m_tabBar->tabData(index).value<FillType>();

    selectTab();

    emit propertyChanged();
}
