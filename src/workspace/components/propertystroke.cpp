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

#include "propertystroke.h"
#include "ui_propertystroke.h"

#include <QPainter>
#include <QDebug>

#include <popupmenu.h>

PropertyStroke::PropertyStroke(QWidget *parent) : PropertyStroke(Stroke("tmpFill", QColor(0,0,0) ), parent){}

PropertyStroke::PropertyStroke(Stroke stroke, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyStroke)
{
    ui->setupUi(this);

    m_colorDialog = new ColorDialog;

    PopupMenu * m_colorMenu = new PopupMenu(m_colorDialog);

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(stroke.color());
    ui->btn_color->setIcon(pixmap);
    ui->btn_color->setMenu(m_colorMenu);

    btn_center = new ButtonGroupButton();
    btn_center->setText("C");
    btn_center->setButtonType(ButtonGroupButton::Type::middle);
    btn_outer = new ButtonGroupButton();
    btn_outer->setText("O");
    btn_outer->setButtonType(ButtonGroupButton::Type::left);
    btn_inner = new ButtonGroupButton();
    btn_inner->setText("I");
    btn_inner->setButtonType(ButtonGroupButton::Type::right);

    m_position = new ButtonGroup();
    m_position->addButton(btn_outer, false);
    m_position->addButton(btn_center, true);
    m_position->addButton(btn_inner, false);

    ui->lyt_position->insertWidget(0, m_position);

    setStroke(stroke);

    connect(ui->btnDelete, &QToolButton::clicked, [this]{
        emit remove(this);
    });
    connect(ui->btn_color, &ColorButton::openPopup, [this]{
        m_colorDialog->setProperty(&m_property);
    });
}

PropertyStroke::~PropertyStroke()
{
    delete ui;
}

void PropertyStroke::setStroke(Stroke stroke)
{
    disconnectSlots();

    m_property = stroke;
    ui->cb_active->setChecked(stroke.isOn());
    ui->sb_width->setValue(stroke.widthF());
 //   m_colorDialog->setProperty(&m_stroke);

    switch(stroke.strokePosition()){
    case Stroke::Center:
            btn_center->setChecked(true);
        break;
    case Stroke::Outer:
            btn_outer->setChecked(true);
        break;
    case Stroke::Inner:
            btn_inner->setChecked(true);
        break;

    }

    drawPreview(stroke);

    connectSlots();
}

Stroke PropertyStroke::stroke() const
{
    return m_property;
}


void PropertyStroke::drawPreview(Stroke stroke)
{
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), stroke.brush());
    ui->btn_color->setIcon(QIcon(pixmap));

}

void PropertyStroke::connectSlots()
{
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyStroke::updateStroke);
    connect(ui->sb_width, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyStroke::updateStroke);
    connect(btn_center, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    connect(btn_inner, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    connect(btn_outer, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    connect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyStroke::updateStroke);
}

void PropertyStroke::disconnectSlots()
{
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyStroke::updateStroke);
    disconnect(ui->sb_width, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyStroke::updateStroke);
    disconnect(btn_center, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    disconnect(btn_inner, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    disconnect(btn_outer, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    disconnect(m_colorDialog, &ColorDialog::propertyChanged, this, &PropertyStroke::updateStroke);
}

void PropertyStroke::updateStroke()
{
    m_property.setColor(m_colorDialog->color());
    m_property.setIsOn(ui->cb_active->isChecked());
    m_property.setBlendMode(m_property.blendMode());  // need real data
    m_property.setBrush(m_property.brush()); // need real data (use brush for solid color too)
    m_property.setWidthF(ui->sb_width->value());

    if(btn_outer->isChecked()){
        m_property.setStrokePosition(Stroke::Outer);
    }else if(btn_inner->isChecked()){
        m_property.setStrokePosition(Stroke::Inner);
    }else m_property.setStrokePosition(Stroke::Center);

    // update preview
    drawPreview(m_property);

    emit hasChanged(true);
}
