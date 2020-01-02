#include "ip_shadows.h"
#include "ui_ip_shadows.h"

ipShadows::ipShadows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipShadows)
{
    ui->setupUi(this);

    unloadItems();
}

ipShadows::~ipShadows()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipShadows::setActiveItem(AbstractItemBase *item)
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

void ipShadows::loadProperties()
{
    switch(m_item->type()){
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Star:
    case AbstractItemBase::Triangle:
        loadShadows();
        break;
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Text:
    default:
        resetItems();
        break;
    }
}


void ipShadows::resetItems()
{
    emit enabled(false);

    m_propertyItemList = new QList<PropertyShadow*>();

    QList<QWidget *> widgets = findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        widget->deleteLater();
    }

}

void ipShadows::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipShadows::loadShadows()
{
    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    foreach(Shadow m_property, m_item->shadowList()){
        PropertyShadow * pf = new PropertyShadow();
        pf->setShadow(m_property);
        addShadow(pf);
    }

    emit enabled(true);
}

void ipShadows::addShadow(PropertyShadow *propertyItem)
{
    connect(propertyItem, &PropertyShadow::hasChanged, this, &ipShadows::updateItem);
    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipShadows::removeShadow(PropertyShadow *propertyItem)
{
    disconnect(propertyItem, &PropertyShadow::hasChanged, this, &ipShadows::updateItem);
    m_propertyItemList->removeOne(propertyItem);
    ui->layout->removeWidget(propertyItem);
}

void ipShadows::newShadow()
{
    if(!m_item) return;

    Shadow m_newProperty;
    PropertyShadow * m_newPropertyItem = new PropertyShadow(m_newProperty);

    m_item->addShadow(m_newProperty);
    m_item->update();
    addShadow(m_newPropertyItem);
}

void ipShadows::updateItem()
{
    PropertyShadow * m_changedProperty = dynamic_cast<PropertyShadow*>(sender());

    if(m_changedProperty && m_item){

       m_item->updateShadow(m_changedProperty->shadow());

    }
}
