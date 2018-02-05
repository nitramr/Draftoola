#include "tool_itemproperties.h"
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
	m_item = item;

//	m_artboard = dynamic_cast<Artboard*>(item);
//	m_itemRect = dynamic_cast<WARect*>(item);
//	m_itemOval = dynamic_cast<WAOval*>(item);
//	m_itemText = dynamic_cast<WAText*>(item);

	if(m_item)
		loadProperties();
}


/***************************************************
 *
 * Members
 *
 ***************************************************/

void ItemProperties::loadProperties()
{

	ui->spinboxXPos->setValue(m_item->pos().x());
	ui->spinboxYPos->setValue(m_item->pos().y());

	this->setEnabled(true);

	switch(m_item->itemType()){

	case ItemType::Artboard:{
		Artboard * item = dynamic_cast<Artboard*>(m_item);

		if(item){
			ui->spinboxWidth->setValue(item->rect().width());
			ui->spinboxHeight->setValue(item->rect().height());
		}

	}
		break;
	case ItemType::Instance:

		break;
	case ItemType::Line:

		break;
	case ItemType::Oval:{
		WAOval * item = dynamic_cast<WAOval*>(m_item);

		if(item){
			ui->spinboxWidth->setValue(item->rect().width());
			ui->spinboxHeight->setValue(item->rect().height());
		}

	}

		break;
	case ItemType::Polygon:

		break;
	case ItemType::Rect:{
		WARect * item = dynamic_cast<WARect*>(m_item);

		if(item){
			ui->spinboxWidth->setValue(item->rect().width());
			ui->spinboxHeight->setValue(item->rect().height());
		}

	}

		break;
	case ItemType::Star:

		break;
	case ItemType::Text:{
		WAText * item = dynamic_cast<WAText*>(m_item);

		if(item){
			ui->spinboxWidth->setValue(item->rect().width());
			ui->spinboxHeight->setValue(item->rect().height());
		}

	}

		break;
	case ItemType::Triangle:

		break;
	default:
		resetItems();
		break;
	}


}

void ItemProperties::resetItems()
{
	this->setEnabled(false);

	// items
	m_item = 0;

	// Properties
	ui->spinboxYPos->setValue(0);
	ui->spinboxXPos->setValue(0);
	ui->spinboxWidth->setValue(0);
	ui->spinboxHeight->setValue(0);

}
