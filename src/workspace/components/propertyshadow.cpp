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

#include "propertyshadow.h"
#include "ui_propertyshadow.h"

#include <popupmenu.h>

PropertyShadow::PropertyShadow(QWidget *parent) : PropertyShadow(Shadow(), parent){}

PropertyShadow::PropertyShadow(Shadow shadow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyShadow)
{
    ui->setupUi(this);

    m_colorDialog = new ColorDialog;

    PopupMenu * m_colorMenu = new PopupMenu(m_colorDialog);

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(shadow.color());
    ui->btn_color->setIcon(pixmap);
    ui->btn_color->setMenu(m_colorMenu);

    setShadow(shadow);
}


PropertyShadow::~PropertyShadow()
{
    delete ui;
}

void PropertyShadow::setShadow(Shadow shadow)
{
    disconnectSlots();

    m_shadow = shadow;
    ui->cb_active->setChecked(shadow.isOn());
    ui->sb_xOffset->setValue(shadow.offset().x());
    ui->sb_yOffset->setValue(shadow.offset().y());
    ui->sb_blur->setValue(shadow.radius());
    ui->sb_spread->setValue(shadow.spread());
    m_colorDialog->setProperty(&m_shadow);

    drawPreview(shadow);

    connectSlots();
}

Shadow PropertyShadow::shadow() const
{
    return m_shadow;
}

void PropertyShadow::drawPreview(Shadow shadow)
{
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), QBrush(shadow.color()));
    ui->btn_color->setIcon(QIcon(pixmap));

}

void PropertyShadow::connectSlots()
{
    connect(ui->btnDelete, &QToolButton::clicked, this, &PropertyShadow::removeClick);
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    connect(ui->sb_blur, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_spread, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_xOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_yOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyShadow::updateShadow);
}

void PropertyShadow::disconnectSlots()
{
    disconnect(ui->btnDelete, &QToolButton::clicked, this, &PropertyShadow::removeClick);
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_blur, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_spread, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_xOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_yOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyShadow::updateShadow);
}

void PropertyShadow::updateShadow()
{
    m_shadow = *m_colorDialog->shadow();
    m_shadow.setIsOn(ui->cb_active->isChecked());
    m_shadow.setOffset(QPointF(ui->sb_xOffset->value(), ui->sb_yOffset->value()));
    m_shadow.setRadius(ui->sb_blur->value());
    m_shadow.setSpread(ui->sb_spread->value());
    m_shadow.setBlendMode(m_shadow.blendMode()); // need real data

    // update preview
    drawPreview(m_shadow);

    emit hasChanged(true);
}

void PropertyShadow::removeClick()
{
    emit remove(this);
}
