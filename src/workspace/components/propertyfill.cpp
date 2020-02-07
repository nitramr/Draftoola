/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

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

#include "propertyfill.h"
#include "ui_propertyfill.h"

#include <QPainter>
#include <QDebug>
#include <popupmenu.h>


PropertyFill::PropertyFill(QWidget *parent) : PropertyFill(Fills(), parent){}
PropertyFill::PropertyFill(Fills fill, QWidget *parent) : QWidget(parent),
ui(new Ui::propertyFill)
{
    ui->setupUi(this);

    m_colorDialog = new ColorDialog;

    PopupMenu * m_colorMenu = new PopupMenu(m_colorDialog);

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(fill.color());
    ui->btn_color->setIcon(pixmap);
    ui->btn_color->setMenu(m_colorMenu);

    // https://doc.qt.io/qt-5/qpainter.html#CompositionMode-enum
    ui->combo_blending->addItem(tr("Normal"), QVariant(QPainter::CompositionMode_SourceOver)); //0
    ui->combo_blending->insertSeparator(ui->combo_blending->count());
    ui->combo_blending->addItem(tr("Darken"), QVariant(QPainter::CompositionMode_Darken)); //16
    ui->combo_blending->addItem(tr("Multiply"), QVariant(QPainter::CompositionMode_Multiply)); //13
    ui->combo_blending->addItem(tr("Color Burn"), QVariant(QPainter::CompositionMode_ColorBurn)); //19
    ui->combo_blending->insertSeparator(ui->combo_blending->count());
    ui->combo_blending->addItem(tr("Lighten"), QVariant(QPainter::CompositionMode_Lighten)); //17
    ui->combo_blending->addItem(tr("Screen"), QVariant(QPainter::CompositionMode_Screen)); //14
    ui->combo_blending->addItem(tr("Color Dodge"), QVariant(QPainter::CompositionMode_ColorDodge)); //18
    ui->combo_blending->insertSeparator(ui->combo_blending->count());
    ui->combo_blending->addItem(tr("Overlay"), QVariant(QPainter::CompositionMode_Overlay)); //15
    ui->combo_blending->addItem(tr("Soft Light"), QVariant(QPainter::CompositionMode_SoftLight)); //21
    ui->combo_blending->addItem(tr("Hard Light"), QVariant(QPainter::CompositionMode_HardLight)); //20
    ui->combo_blending->addItem(tr("Difference"), QVariant(QPainter::CompositionMode_Difference)); //22
    ui->combo_blending->addItem(tr("Exclusion"), QVariant(QPainter::CompositionMode_Exclusion)); //23
    ui->combo_blending->insertSeparator(ui->combo_blending->count());
    ui->combo_blending->addItem(tr("Plus"), QVariant(QPainter::CompositionMode_Plus)); //12

    setFill(fill);

    connect(ui->btnDelete, &QToolButton::clicked, [this]{
        emit remove(this);
    });
    connect(ui->btn_color, &ColorButton::openPopup, [this]{
        m_colorDialog->setProperty(&m_property);
    });
}

PropertyFill::~PropertyFill()
{
    delete ui;
}

void PropertyFill::setFill(Fills fill)
{
    disconnectSlots();

    m_property = fill;

    ui->cb_active->setChecked(fill.isOn());
    ui->sb_opacity->setValue( (m_property.fillType() == FillType::Color) ?
                                  qRound(m_property.color().alphaF()* 100) :
                                  qRound(m_property.opacity() * 100) );

    int indexMode = 0;
    for(int i = 0; i < ui->combo_blending->count(); i++){
        if(fill.blendMode() == static_cast<QPainter::CompositionMode>(ui->combo_blending->itemData(i).toInt())){
            indexMode = i;
            break;
        }
    }

    ui->combo_blending->setCurrentIndex(indexMode);
    drawFill(fill);

    connectSlots();
}

Fills PropertyFill::fill() const
{
    return m_property;
}

void PropertyFill::drawFill(Fills property)
{
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);


    switch (property.fillType()) {
    case FillType::Color:{
        painter.fillRect(pixmap.rect(), QBrush(property.color()));
        break;
    }
    case FillType::RadialGradient:
        painter.setOpacity(property.opacity());
        painter.fillRect(pixmap.rect(), QBrush(property.gradient().radial(pixmap.rect())));
        break;
    case FillType::ConicalGradient:
        painter.setOpacity(property.opacity());
        painter.fillRect(pixmap.rect(), QBrush(property.gradient().conical(pixmap.rect())));
        break;
    case FillType::LinearGradient:
        painter.setOpacity(property.opacity());
        painter.fillRect(pixmap.rect(), QBrush(property.gradient().linear(pixmap.rect())));
        break;
    case FillType::Image:
        painter.setOpacity(property.opacity());
        painter.drawPixmap(pixmap.rect(), property.pixmap(), property.pixmap().rect());
        break;
    case FillType::Pattern:
        break;
    default:
        break;
    }

    ui->btn_color->setIcon(pixmap);
}

void PropertyFill::connectSlots()
{
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyFill::updateProperty);
    connect(ui->sb_opacity, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertyFill::updateOpacity);
    connect(ui->combo_blending, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyFill::updateProperty);
    connect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyFill::updateFill);
}

void PropertyFill::disconnectSlots()
{
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyFill::updateProperty);
    disconnect(ui->sb_opacity, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertyFill::updateOpacity);
    disconnect(ui->combo_blending, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyFill::updateProperty);
    disconnect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyFill::updateFill);
}

void PropertyFill::updateProperty()
{
    m_property.setIsOn(ui->cb_active->isChecked());
    m_property.setBlendMode(static_cast<QPainter::CompositionMode>(ui->combo_blending->currentData().toInt()) );

    // update preview
    drawFill(m_property);

    emit hasChanged(true);
}

void PropertyFill::updateFill()
{
    m_property.setColor(m_colorDialog->color());
    m_property.setOpacity(m_colorDialog->opacity());
    m_property.setPixmap(m_colorDialog->pixmap());
    m_property.setGradient(m_colorDialog->gradient());
    m_property.setFillType(m_colorDialog->fillType()); // set which type should used

    disconnectSlots();
    ui->sb_opacity->setValue( (m_property.fillType() == FillType::Color) ?
                                  qRound(m_property.color().alphaF()* 100) :
                                  qRound(m_property.opacity() * 100) );
    connectSlots();

    updateProperty();
}

void PropertyFill::updateOpacity()
{

    // if fill type is "color" opacity widget controls directly alpha channel of color
    if(m_property.fillType() == FillType::Color){
        Color col = m_property.color();
        col.setAlphaF(ui->sb_opacity->value()/100.0);
        m_property.setColor(col);
    }else m_property.setOpacity( ui->sb_opacity->value()/100.0 );

    updateProperty();
}

