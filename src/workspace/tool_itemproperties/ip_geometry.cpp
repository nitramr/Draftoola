#include "ip_geometry.h"
#include "ui_ip_geometry.h"

#include <abstractitembase.h>
#include <itempolygon.h>

ipGeometry::ipGeometry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ip_geometry)
{
    ui->setupUi(this);

    btnFree = new ButtonGroupButton();
    btnFree->setButtonType(ButtonGroupButton::left);
    btnFree->setIcon(QIcon(":/icons/dark/frame-free.svg"));
    btnFree->setData(AbstractItemBase::Free);

    btnFixedWidth = new ButtonGroupButton();
    btnFixedWidth->setButtonType(ButtonGroupButton::middle);
    btnFixedWidth->setIcon(QIcon(":/icons/dark/frame-horizontal-lock.svg"));
    btnFixedWidth->setData(AbstractItemBase::FixedWidth);

    btnFixedHeight = new ButtonGroupButton();
    btnFixedHeight->setButtonType(ButtonGroupButton::middle);
    btnFixedHeight->setIcon(QIcon(":/icons/dark/frame-vertical-lock.svg"));
    btnFixedHeight->setData(AbstractItemBase::FixedHeight);

    btnFixedSize = new ButtonGroupButton();
    btnFixedSize->setButtonType(ButtonGroupButton::right);
    btnFixedSize->setIcon(QIcon(":/icons/dark/frame-all-lock.svg"));
    btnFixedSize->setData(AbstractItemBase::FixedSize);

    btnGroup = new ButtonGroup();
    btnGroup->addButton(btnFree, true);
    btnGroup->addButton(btnFixedHeight, false);
    btnGroup->addButton(btnFixedWidth, false);
    btnGroup->addButton(btnFixedSize, false);

    ui->frameLayout->addWidget(btnGroup);
    ui->frameLayout->addStretch();

    unloadItems();

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
    case AbstractItemBase::Polygon:
    case AbstractItemBase::Instance:
    case AbstractItemBase::Line:
    case AbstractItemBase::Text:
    case AbstractItemBase::Group:
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

    updateFrameState( m_item->frameType() );


    switch(m_item->type()){
    case AbstractItemBase::Type::Polygon:
        ItemPolygon * plyItem = dynamic_cast<ItemPolygon*>(m_item);
        if(plyItem){
            ui->spinBoxPolygonPoints->setValue(plyItem->sides());
            ui->spinBoxPolygonRadius->setValue(qRound(plyItem->innerRadius() * 100));
            ui->lbl_polygonPoints->setVisible(true);
            ui->spinBoxPolygonPoints->setVisible(true);
            if(plyItem->useInnerRadius()){
                ui->lbl_polygonRadius->setVisible(true);
                ui->spinBoxPolygonRadius->setVisible(true);
            }else{
                ui->lbl_polygonRadius->setVisible(false);
                ui->spinBoxPolygonRadius->setVisible(false);
            }

        }
        break;
    }


    connectSlots();
}


void ipGeometry::resetItems()
{
    disconnectSlots();

    ui->spinboxYPos->setValue(0);
    ui->spinboxXPos->setValue(0);
    ui->spinboxWidth->setValue(0);
    ui->spinboxHeight->setValue(0);
    btnFree->setChecked(true);
    ui->spinboxWidth->setEnabled(true);
    ui->spinboxHeight->setEnabled(true);

    ui->lbl_polygonPoints->setVisible(false);
    ui->lbl_polygonRadius->setVisible(false);
    ui->spinBoxPolygonPoints->setVisible(false);
    ui->spinBoxPolygonRadius->setVisible(false);

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
    connect(btnGroup, &ButtonGroup::buttonClicked, this, &ipGeometry::updateItem);
    connect(ui->spinBoxPolygonPoints, QOverload<int>::of(&QSpinBox::valueChanged), this, &ipGeometry::updateItem);
    connect(ui->spinBoxPolygonRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &ipGeometry::updateItem);
}

void ipGeometry::disconnectSlots()
{
    disconnect(ui->spinboxXPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxYPos, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxWidth, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinboxHeight, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(btnGroup, &ButtonGroup::buttonClicked, this, &ipGeometry::updateItem);
    disconnect(ui->spinBoxPolygonPoints, QOverload<int>::of(&QSpinBox::valueChanged), this, &ipGeometry::updateItem);
    disconnect(ui->spinBoxPolygonRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &ipGeometry::updateItem);
}

void ipGeometry::updateFrameState(AbstractItemBase::FrameType frameType)
{
    switch(frameType){
    case AbstractItemBase::Free:
        btnFree->setChecked(true);
        ui->spinboxWidth->setEnabled(true);
        ui->spinboxHeight->setEnabled(true);
        break;
    case AbstractItemBase::FixedWidth:
        btnFixedWidth->setChecked(true);
        ui->spinboxWidth->setEnabled(false);
        ui->spinboxHeight->setEnabled(true);
        break;
    case AbstractItemBase::FixedHeight:
        btnFixedHeight->setChecked(true);
        ui->spinboxWidth->setEnabled(true);
        ui->spinboxHeight->setEnabled(false);
        break;
    case AbstractItemBase::FixedSize:
        btnFixedSize->setChecked(true);
        ui->spinboxWidth->setEnabled(false);
        ui->spinboxHeight->setEnabled(false);
        break;
    }
}

void ipGeometry::updateItem()
{
    if(m_item){

        m_item->setRect(QRectF(0,0,ui->spinboxWidth->value(), ui->spinboxHeight->value()));
        m_item->setPos(QPointF(ui->spinboxXPos->value(), ui->spinboxYPos->value()));

        ButtonGroupButton * activeButton = dynamic_cast<ButtonGroupButton*>( btnGroup->checkedButton() );

        if(activeButton){
            m_item->setFrameType( static_cast<AbstractItemBase::FrameType>(activeButton->data().toInt() ) );
            updateFrameState( m_item->frameType() );
        }

        switch(m_item->type()){
        case AbstractItemBase::Type::Polygon:
            ItemPolygon * plyItem = dynamic_cast<ItemPolygon*>(m_item);
            if(plyItem){

                plyItem->setSides(ui->spinBoxPolygonPoints->value());
                plyItem->setInnerRadius(ui->spinBoxPolygonRadius->value() / 100.0);

            }
            break;
        }

        emit itemsChanged();

    }
}
