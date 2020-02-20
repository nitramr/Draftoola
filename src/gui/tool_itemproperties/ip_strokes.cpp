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

#include "ip_strokes.h"
#include "ui_ip_strokes.h"

ipStrokes::ipStrokes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipStrokes)
{
    ui->setupUi(this);

    unloadItems();
}

ipStrokes::~ipStrokes()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipStrokes::setActiveItem(AbstractItemBase *item)
{    
    ItemBase *activeItem = dynamic_cast<ItemBase*>(item);

    if(activeItem){
        if(activeItem != m_item){
            m_item = activeItem;
            loadProperties();
        }
    }else{
        unloadItems();
    }

}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void ipStrokes::loadProperties()
{
    switch(m_item->type()){
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Polygon:
    case AbstractItemBase::Line:
    case AbstractItemBase::Text:
        loadStrokes();
        break;
    case AbstractItemBase::Instance:
    case AbstractItemBase::Group:
    default:
        resetItems();
        break;
    }
}


void ipStrokes::resetItems()
{
    emit enabled(false);

    m_propertyItemList = new QList<PropertyStroke*>();

    QList<QWidget *> widgets = findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        widget->deleteLater();
    }

}

void ipStrokes::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipStrokes::loadStrokes()
{
    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    foreach(Stroke m_property, m_item->strokeList()){
        PropertyStroke * pf = new PropertyStroke(m_property);
        addStroke(pf);
    }

    emit enabled(true);
}

void ipStrokes::addStroke(PropertyStroke *propertyItem)
{
    connect(propertyItem, &PropertyStroke::hasChanged, this, &ipStrokes::updateItem);
    connect(propertyItem, &PropertyStroke::remove, this, &ipStrokes::removeStroke );
    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipStrokes::removeStroke(PropertyStroke *propertyItem)
{
    if(m_item == nullptr) return;

    disconnect(propertyItem, &PropertyStroke::hasChanged, this, &ipStrokes::updateItem);
    disconnect(propertyItem, &PropertyStroke::remove, this, &ipStrokes::removeStroke );
    m_propertyItemList->removeOne(propertyItem);
    m_item->removeStroke(propertyItem->stroke());
    ui->layout->removeWidget(propertyItem);

    propertyItem->deleteLater();

    if(m_propertyItemList->count() <= 0){
        this->setEnabled(false);
        emit sendCollapse(true);
    }
}

void ipStrokes::newStroke()
{
    if(!m_item) return;

    Stroke m_newProperty;
    PropertyStroke * m_newPropertyItem= new PropertyStroke(m_newProperty);

    m_item->addStroke(m_newProperty);
    m_item->update();
    addStroke(m_newPropertyItem);

    if(m_propertyItemList->count() == 1){
        this->setEnabled(true);
        emit sendCollapse(false);
    }
}

void ipStrokes::updateItem()
{
    PropertyStroke * m_changedProperty = dynamic_cast<PropertyStroke*>(sender());

    if(m_changedProperty && m_item){

        m_item->updateStroke(m_changedProperty->stroke());
        emit itemsChanged();
    }

}
