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

#include "ip_exportlevel.h"
#include "ui_ip_exportlevel.h"

ipExportLevels::ipExportLevels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipExportLevel)
{
    ui->setupUi(this);

    unloadItems();

    connect(ui->btnExport, &QPushButton::clicked, this, &ipExportLevels::doExport);
}

ipExportLevels::~ipExportLevels()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipExportLevels::setActiveItem(AbstractItemBase *item)
{    
    AbstractItemBase *activeItem = item;

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

void ipExportLevels::loadProperties()
{
    switch(m_item->type()){
    case AbstractItemBase::Artboard:
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Polygon:
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Text:
    case AbstractItemBase::Group:
        loadExportLevels();
        break;
    default:
        resetItems();
        break;
    }
}


void ipExportLevels::resetItems()
{

    m_propertyItemList = new QList<PropertyExportLevel*>();

    this->setEnabled(false);

    QLayout *lyt = ui->lytItems;
    while(!lyt->isEmpty()) {
        QWidget *w = lyt->takeAt(0)->widget();
        delete w;
    }

}

void ipExportLevels::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipExportLevels::loadExportLevels()
{
    emit sendCollapse(false);

    resetItems();

    foreach(ExportLevel m_exportLevel, m_item->exportLevels()){
        PropertyExportLevel * pf = new PropertyExportLevel();
        pf->setExportLevel(m_exportLevel);
        addExportLevel(pf);
    }

    if(m_item->exportLevels().count() > 0) this->setEnabled(true);
}

void ipExportLevels::addExportLevel(PropertyExportLevel *propertyItem)
{
    connect(propertyItem, &PropertyExportLevel::hasChanged, this, &ipExportLevels::updateItem);
    connect(propertyItem, &PropertyExportLevel::remove, this, &ipExportLevels::removeExportLevel );

    m_propertyItemList->append(propertyItem);
    ui->lytItems->addWidget(propertyItem);

}

void ipExportLevels::removeExportLevel(PropertyExportLevel *propertyItem)
{
    if(m_item == nullptr) return;

    disconnect(propertyItem, &PropertyExportLevel::hasChanged, this, &ipExportLevels::updateItem);
    disconnect(propertyItem, &PropertyExportLevel::remove, this, &ipExportLevels::removeExportLevel );

    m_propertyItemList->removeOne(propertyItem);
    m_item->removeExportLevel(propertyItem->exportLevel());
    ui->lytItems->removeWidget(propertyItem);

    propertyItem->deleteLater();

    if(m_propertyItemList->count() <= 0){
        this->setEnabled(false);
        emit sendCollapse(true);
    }

}

void ipExportLevels::newExportLevel()
{
    if(m_item == nullptr) return;

    PropertyExportLevel *newExportLevel = new PropertyExportLevel();
    addExportLevel(newExportLevel);

    m_item->addExportLevel(newExportLevel->exportLevel());

    if(m_propertyItemList->count() == 1){
        this->setEnabled(true);
        emit sendCollapse(false);
    }

}

void ipExportLevels::updateItem()
{
    PropertyExportLevel * m_changedProperty = dynamic_cast<PropertyExportLevel*>(sender());

    if(m_changedProperty && m_item){

        m_item->updateExportLevel(m_changedProperty->exportLevel());
        emit itemsChanged();
    }

}

void ipExportLevels::doExport()
{
    if(m_item == nullptr) return;
    emit exportItem(m_item);

}
