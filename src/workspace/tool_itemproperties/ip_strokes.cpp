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

    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    switch(m_item->itemType()){
    case ItemType::Oval:
    case ItemType::Polygon:
    case ItemType::Rect:
    case ItemType::Star:
    case ItemType::Triangle:
        loadStrokes();
        break;
    case ItemType::Instance:
    case ItemType::Line:
    case ItemType::Text:
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
    foreach(Stroke m_property, m_item->strokeList()){
        PropertyStroke * pf = new PropertyStroke();
        pf->setStroke(m_property);
        addStroke(pf);
    }

    emit enabled(true);
}

void ipStrokes::addStroke(PropertyStroke *propertyItem)
{
    connect(propertyItem, &PropertyStroke::hasChanged, this, &ipStrokes::updateItem);
    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipStrokes::removeStroke(PropertyStroke *propertyItem)
{
    disconnect(propertyItem, &PropertyStroke::hasChanged, this, &ipStrokes::updateItem);
    m_propertyItemList->removeOne(propertyItem);
    ui->layout->removeWidget(propertyItem);
}

void ipStrokes::newStroke()
{
    if(!m_item) return;

    Stroke m_newProperty;
    PropertyStroke * m_newPropertyItem= new PropertyStroke(m_newProperty);

    m_item->addStroke(m_newProperty);
    m_item->update();
    addStroke(m_newPropertyItem);
}

void ipStrokes::updateItem()
{
    PropertyStroke * m_changedProperty = dynamic_cast<PropertyStroke*>(sender());

    if(m_changedProperty && m_item){

       m_item->updateStroke(m_changedProperty->stroke());

    }
}
