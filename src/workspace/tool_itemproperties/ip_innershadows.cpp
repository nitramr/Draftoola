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

#include "ip_innershadows.h"
#include "ui_ip_shadows.h"

ipInnerShadows::ipInnerShadows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipShadows)
{
    ui->setupUi(this);

    unloadItems();
}

ipInnerShadows::~ipInnerShadows()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipInnerShadows::setActiveItem(AbstractItemBase *item)
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

void ipInnerShadows::loadProperties()
{
    switch(m_item->type()){
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Polygon:
    case AbstractItemBase::Text:
        loadShadows();
        break;
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Group:
    default:
        resetItems();
        break;
    }
}


void ipInnerShadows::resetItems()
{
    emit enabled(false);

    m_propertyItemList = new QList<PropertyShadow*>();

    QList<QWidget *> widgets = findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        widget->deleteLater();
    }
}

void ipInnerShadows::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipInnerShadows::loadShadows()
{
    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    foreach(Shadow m_property, m_item->innerShadowList()){
        PropertyShadow * pf = new PropertyShadow();
        pf->setShadow(m_property);
        addShadow(pf);
    }
    emit enabled(true);
}

void ipInnerShadows::addShadow(PropertyShadow *propertyItem)
{
    connect(propertyItem, &PropertyShadow::hasChanged, this, &ipInnerShadows::updateItem);
    connect(propertyItem, &PropertyShadow::remove, this, &ipInnerShadows::removeShadow );

    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipInnerShadows::removeShadow(PropertyShadow *propertyItem)
{
    if(m_item == nullptr) return;

    disconnect(propertyItem, &PropertyShadow::hasChanged, this, &ipInnerShadows::updateItem);
    disconnect(propertyItem, &PropertyShadow::remove, this, &ipInnerShadows::removeShadow );
    m_propertyItemList->removeOne(propertyItem);
    m_item->removeInnerShadow(propertyItem->shadow());
    ui->layout->removeWidget(propertyItem);

    propertyItem->deleteLater();

    if(m_propertyItemList->count() <= 0){
        this->setEnabled(false);
        emit sendCollapse(true);
    }
}

void ipInnerShadows::newShadow()
{
    if(!m_item) return;

    Shadow m_newProperty;
    PropertyShadow * m_newPropertyItem = new PropertyShadow(m_newProperty);

    m_item->addInnerShadow(m_newProperty);
    m_item->update();
    addShadow(m_newPropertyItem);

    if(m_propertyItemList->count() == 1){
        this->setEnabled(true);
        emit sendCollapse(false);
    }
}

void ipInnerShadows::updateItem()
{
    PropertyShadow * m_changedProperty = dynamic_cast<PropertyShadow*>(sender());

    if(m_changedProperty && m_item){

        m_item->updateInnerShadow(m_changedProperty->shadow());
        emit itemsChanged();
    }
}
