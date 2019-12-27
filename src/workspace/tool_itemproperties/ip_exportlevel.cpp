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

    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    switch(m_item->itemType()){
    case ItemType::Oval:
    case ItemType::Polygon:
    case ItemType::Rect:
    case ItemType::Star:
    case ItemType::Triangle:
    case ItemType::Instance:
    case ItemType::Line:
    case ItemType::Text:
        loadExportLevels();
        break;
    default:
        resetItems();
        break;
    }
}


void ipExportLevels::resetItems()
{

    m_exportLevelItemList = new QList<PropertyExportLevel*>();

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
    foreach(ExportLevel m_exportLevel, m_item->exportLevels()){
        PropertyExportLevel * pf = new PropertyExportLevel();
        pf->setExportLevel(m_exportLevel);
        addExportLevel(pf);
    }
}

void ipExportLevels::addExportLevel(PropertyExportLevel *propertyItem)
{
    connect(propertyItem, &PropertyExportLevel::hasChanged, this, &ipExportLevels::updateItem);
    connect(propertyItem, &PropertyExportLevel::remove, this, &ipExportLevels::removeExportLevel );

    m_exportLevelItemList->append(propertyItem);
    ui->lytItems->addWidget(propertyItem);


}

void ipExportLevels::removeExportLevel(PropertyExportLevel *propertyItem)
{
    if(m_item == nullptr) return;

    disconnect(propertyItem, &PropertyExportLevel::hasChanged, this, &ipExportLevels::updateItem);
    disconnect(propertyItem, &PropertyExportLevel::remove, this, &ipExportLevels::removeExportLevel );

    m_exportLevelItemList->removeOne(propertyItem);
    m_item->removeExportLevel(propertyItem->exportLevel());
    ui->lytItems->removeWidget(propertyItem);

    propertyItem->deleteLater();

    if(m_exportLevelItemList->count() <= 0){
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

    if(m_exportLevelItemList->count() == 1){
        this->setEnabled(true);
        emit sendCollapse(false);
    }

}

void ipExportLevels::updateItem()
{
    PropertyExportLevel * m_changedProperty = dynamic_cast<PropertyExportLevel*>(sender());

    if(m_changedProperty && m_item){

       m_item->updateExportLevel(m_changedProperty->exportLevel());

    }

}

void ipExportLevels::doExport()
{
    if(m_item == nullptr) return;
    emit exportItem(m_item);

}