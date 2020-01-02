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
    switch(m_item->type()){
    case AbstractItemBase::Artboard:
    case AbstractItemBase::Oval:
    case AbstractItemBase::Path:
    case AbstractItemBase::Rect:
    case AbstractItemBase::Star:
    case AbstractItemBase::Triangle:
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Text:
        loadGeometry();
        break;
    default:
        resetItems();
        break;
    }

}

void ipGeometry::loadGeometry()
{
    this->setEnabled(true);
    resetItems();

    disconnectSlots();

    ui->spinboxXPos->setValue(m_item->pos().x());
    ui->spinboxYPos->setValue(m_item->pos().y());
    ui->spinboxWidth->setValue(m_item->rect().width());
    ui->spinboxHeight->setValue(m_item->rect().height());

    connectSlots();
}


void ipGeometry::resetItems()
{
    disconnectSlots();

    ui->spinboxYPos->setValue(0);
    ui->spinboxXPos->setValue(0);
    ui->spinboxWidth->setValue(0);
    ui->spinboxHeight->setValue(0);

    connectSlots();
}

void ipGeometry::unloadItems()
{
    this->setEnabled(false);
    m_item = nullptr;
    resetItems();
}

void ipGeometry::connectSlots()
{
    connect(ui->spinboxXPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    connect(ui->spinboxYPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    connect(ui->spinboxWidth, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    connect(ui->spinboxHeight, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);

}

void ipGeometry::disconnectSlots()
{
    disconnect(ui->spinboxXPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxYPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxWidth, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxHeight, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
}

void ipGeometry::updateItem()
{
 if(m_item){

      m_item->setRect(QRectF(0,0,ui->spinboxWidth->value(), ui->spinboxHeight->value()));
      m_item->setPos(QPointF(ui->spinboxXPos->value(), ui->spinboxYPos->value()));

    }
}
