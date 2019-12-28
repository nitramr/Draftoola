#include "ip_fills.h"
#include "ui_ip_fills.h"

ipFills::ipFills(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipFills)
{
    ui->setupUi(this);

    unloadItems();
}

ipFills::~ipFills()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipFills::setActiveItem(AbstractItemBase *item)
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

void ipFills::loadProperties()
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
        loadFills();
        break;
    case ItemType::Instance:
    case ItemType::Line:
    case ItemType::Text:
    default:
        resetItems();
        break;
    }
}


void ipFills::resetItems()
{
    emit enabled(false);

    m_propertyItemList = new QList<PropertyFill*>();

    QList<QWidget *> widgets = findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        widget->deleteLater();
    }
}

void ipFills::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipFills::loadFills()
{
    foreach(Fills m_property, m_item->fillsList()){
        PropertyFill * pf = new PropertyFill();
        pf->setFill(m_property);
        addFill(pf);
    }

    emit enabled(true);
}

void ipFills::addFill(PropertyFill *propertyItem)
{
    connect(propertyItem, &PropertyFill::hasChanged, this, &ipFills::updateItem);

    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipFills::removeFill(PropertyFill *propertyItem)
{
    disconnect(propertyItem, &PropertyFill::hasChanged, this, &ipFills::updateItem);

    m_propertyItemList->removeOne(propertyItem);
    ui->layout->removeWidget(propertyItem);
}

void ipFills::newFill()
{
    if(!m_item) return;

    Fills m_newProperty;
    PropertyFill * m_newPropertyItem = new PropertyFill(m_newProperty);

    m_item->addFills(m_newProperty);
    m_item->update();
    addFill(m_newPropertyItem);
}

void ipFills::updateItem()
{
    PropertyFill * m_changedProperty = dynamic_cast<PropertyFill*>(sender());

    if(m_changedProperty && m_item){

       m_item->updateFills(m_changedProperty->fill());

    }

}
