#include "ip_geometry.h"
#include "ui_ip_geometry.h"

ipGeometry::ipGeometry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ip_geometry)
{
    ui->setupUi(this);

}

ipGeometry::~ipGeometry()
{
    delete ui;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipGeometry::setActiveItem(AbstractItemBase *item)
{
    m_item = item;

    if(m_item){
        loadProperties();
    }else{
        unloadItems();
    }
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void ipGeometry::loadProperties()
{
    this->setEnabled(true);
    resetItems();

    loadGeometry();

//    switch(m_item->itemType()){

//    case ItemType::Artboard:{
//        Artboard * item = dynamic_cast<Artboard*>(m_item);

//        if(item){
//           // Artboard
//        }

//    }
//        break;
//    case ItemType::Instance:

//        break;
//    case ItemType::Line:

//        break;
//    case ItemType::Oval:

//        break;
//    case ItemType::Polygon:

//        break;
//    case ItemType::Rect:

//        break;
//    case ItemType::Star:

//        break;
//    case ItemType::Text:

//        break;
//    case ItemType::Triangle:

//        break;
//    default:
//        resetItems();
//        break;
//    }

}

void ipGeometry::loadGeometry()
{
    ui->spinboxXPos->setValue(m_item->pos().x());
    ui->spinboxYPos->setValue(m_item->pos().y());
    ui->spinboxWidth->setValue(m_item->rect().width());
    ui->spinboxHeight->setValue(m_item->rect().height());
}


void ipGeometry::resetItems()
{
    ui->spinboxYPos->setValue(0);
    ui->spinboxXPos->setValue(0);
    ui->spinboxWidth->setValue(0);
    ui->spinboxHeight->setValue(0);
}

void ipGeometry::unloadItems()
{
    this->setEnabled(false);
    m_item = nullptr;
    resetItems();
}

void ipGeometry::updateItem()
{

}
