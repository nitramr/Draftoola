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
    switch(m_item->type()){
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Polygon:
    case AbstractItemBase::Text:
        loadFills();
        break;
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Group:
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
    resetItems();

    foreach(Fills m_property, m_item->fillsList()){
        PropertyFill * pf = new PropertyFill();
        pf->setFill(m_property);
        addFill(pf);
    }

    this->setEnabled(true);
    emit sendCollapse(false);

    emit enabled(true);
}

void ipFills::addFill(PropertyFill *propertyItem)
{
    connect(propertyItem, &PropertyFill::hasChanged, this, &ipFills::updateItem);
    connect(propertyItem, &PropertyFill::remove, this, &ipFills::removeFill );

    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipFills::removeFill(PropertyFill *propertyItem)
{
    if(m_item == nullptr) return;

    disconnect(propertyItem, &PropertyFill::hasChanged, this, &ipFills::updateItem);
    disconnect(propertyItem, &PropertyFill::remove, this, &ipFills::removeFill );
    m_propertyItemList->removeOne(propertyItem);
    m_item->removeFills(propertyItem->fill());
    ui->layout->removeWidget(propertyItem);

    propertyItem->deleteLater();

    if(m_propertyItemList->count() <= 0){
        this->setEnabled(false);
        emit sendCollapse(true);
    }
}

void ipFills::newFill()
{
    if(!m_item) return;

    Fills m_newProperty;
    PropertyFill * m_newPropertyItem = new PropertyFill(m_newProperty);

    m_item->addFills(m_newProperty);
    m_item->update();
    addFill(m_newPropertyItem);

    if(m_propertyItemList->count() == 1){
        this->setEnabled(true);
        emit sendCollapse(false);
    }
}

void ipFills::updateItem()
{
    PropertyFill * m_changedProperty = dynamic_cast<PropertyFill*>(sender());

    if(m_changedProperty && m_item){

        m_item->updateFills(m_changedProperty->fill());
        emit itemsChanged();
    }

}
