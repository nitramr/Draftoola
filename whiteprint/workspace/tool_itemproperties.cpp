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

void ItemProperties::setActiveItem(QGraphicsItem *item)
{

	resetItems();

	m_artboard = dynamic_cast<Artboard*>(item);
	m_itemRect = dynamic_cast<WARect*>(item);
	m_itemOval = dynamic_cast<WAOval*>(item);
	m_itemText = dynamic_cast<WAText*>(item);

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
	}else if(m_itemRect){

		ui->spinboxXPos->setValue(m_itemRect->pos().x());
		ui->spinboxYPos->setValue(m_itemRect->pos().y());
		ui->spinboxWidth->setValue(m_itemRect->rect().width());
		ui->spinboxHeight->setValue(m_itemRect->rect().height());

		this->setEnabled(true);
	}else if(m_itemOval){

		ui->spinboxXPos->setValue(m_itemOval->pos().x());
		ui->spinboxYPos->setValue(m_itemOval->pos().y());
		ui->spinboxWidth->setValue(m_itemOval->rect().width());
		ui->spinboxHeight->setValue(m_itemOval->rect().height());

		this->setEnabled(true);
	}else if(m_itemText){

		ui->spinboxXPos->setValue(m_itemText->pos().x());
		ui->spinboxYPos->setValue(m_itemText->pos().y());
		ui->spinboxWidth->setValue(m_itemText->rect().width());
		ui->spinboxHeight->setValue(m_itemText->rect().height());

		this->setEnabled(true);
	}else resetItems();

}

void ItemProperties::resetItems()
{
	this->setEnabled(false);

	// items
	m_artboard = 0;
	m_itemRect = 0;
	m_itemOval = 0;
	m_itemText = 0;

	// Properties
	ui->spinboxYPos->setValue(0);
	ui->spinboxXPos->setValue(0);
	ui->spinboxWidth->setValue(0);
	ui->spinboxHeight->setValue(0);

}
