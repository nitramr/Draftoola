#include "itemproperties.h"
#include "ui_itemproperties.h"

#include "whiteprint/item/waoval.h"
#include "whiteprint/item/warect.h"

#include <QDebug>

ItemProperties::ItemProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemProperties)
{
    ui->setupUi(this);

    resetItems();
}

ItemProperties::~ItemProperties()
{
    delete ui;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemProperties::setActiveItem(ItemBase *item)
{

    resetItems();

    m_artboard = dynamic_cast<Artboard*>(item);
    m_item = item;

    loadProperties();
}


/***************************************************
 *
 * Members
 *
 ***************************************************/

void ItemProperties::loadProperties()
{
    if(m_artboard){

        ui->spinboxXPos->setValue(m_artboard->pos().x());
        ui->spinboxYPos->setValue(m_artboard->pos().y());
        ui->spinboxWidth->setValue(m_artboard->rect().width());
        ui->spinboxHeight->setValue(m_artboard->rect().height());

        this->setEnabled(true);
    }else if(m_item){

        ui->spinboxXPos->setValue(m_item->pos().x());
        ui->spinboxYPos->setValue(m_item->pos().y());
        ui->spinboxWidth->setValue(m_item->rect().width());
        ui->spinboxHeight->setValue(m_item->rect().height());

        this->setEnabled(true);
    }else resetItems();

}

void ItemProperties::resetItems()
{
    this->setEnabled(false);

    // items
    m_artboard = 0;
    m_item = 0;

    // Properties
    ui->spinboxYPos->setValue(0);
    ui->spinboxXPos->setValue(0);
    ui->spinboxWidth->setValue(0);
    ui->spinboxHeight->setValue(0);

}
