#include "tool_itemproperties.h"
#include "ui_tool_itemproperties.h"

#include "src/widgets/layoutsection.h"

#include "src/item/itemoval.h"
#include "src/item/itemrect.h"

#include <QDebug>


ItemProperties::ItemProperties(QScrollArea *container, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemProperties), m_container(container)
{
    ui->setupUi(this);   


    setupGeometry();
    setupFills();
    setupStrokes();
    setupShadows();
    setupInnerShadows();
    setupExportLevel();

    ui->layout->addStretch(1);

    m_container->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    m_container->setWidget(this);
    m_container->setWidgetResizable(true);
    m_container->setFrameStyle(0);
    m_container->setSizePolicy(QSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding));

}

ItemProperties::~ItemProperties()
{
	delete ui;
}

/***************************************************
 *
 * Setup
 *
 ***************************************************/

void ItemProperties::setupGeometry()
{
    itemGeometry = new ipGeometry();
    LayoutSection *m_section = new LayoutSection(tr("Geometry"));
    m_section->addWidget(itemGeometry);

    ui->layout->addWidget(m_section);
}


void ItemProperties::setupFills()
{
    itemFills = new ipFills();

    QToolButton *btn_Addnew = new QToolButton;
    btn_Addnew->setIcon( QIcon(":/icons/dark/plus.svg") );

    LayoutSection *m_section = new LayoutSection(tr("Fills"), nullptr, true);
    m_section->addWidget(itemFills);
    m_section->setCollapsedState(true);
    m_section->addButton(btn_Addnew);

    this->connect(btn_Addnew, &QToolButton::clicked, itemFills, &ipFills::newFill);
    this->connect(itemFills, &ipFills::sendCollapse, m_section, &LayoutSection::setCollapsedState);

    ui->layout->addWidget(m_section);
}


void ItemProperties::setupStrokes()
{
    itemStrokes = new ipStrokes();

    QToolButton *btn_Addnew = new QToolButton;
    btn_Addnew->setIcon( QIcon(":/icons/dark/plus.svg") );

    LayoutSection *m_section = new LayoutSection(tr("Strokes"), nullptr, true);
    m_section->addWidget(itemStrokes);
    m_section->setCollapsedState(true);
    m_section->addButton(btn_Addnew);

    this->connect(btn_Addnew, &QToolButton::clicked, itemStrokes, &ipStrokes::newStroke);
    this->connect(itemStrokes, &ipStrokes::sendCollapse, m_section, &LayoutSection::setCollapsedState);

    ui->layout->addWidget(m_section);
}


void ItemProperties::setupShadows()
{
    itemShadows = new ipShadows();

    QToolButton *btn_Addnew = new QToolButton;
    btn_Addnew->setIcon( QIcon(":/icons/dark/plus.svg") );

    LayoutSection *m_section = new LayoutSection(tr("Shadows"), nullptr, true);
    m_section->addWidget(itemShadows);
    m_section->setCollapsedState(true);
    m_section->addButton(btn_Addnew);

    this->connect(btn_Addnew, &QToolButton::clicked, itemShadows, &ipShadows::newShadow);
    this->connect(itemShadows, &ipShadows::sendCollapse, m_section, &LayoutSection::setCollapsedState);

    ui->layout->addWidget(m_section);
}

void ItemProperties::setupInnerShadows()
{
    itemInnerShadows = new ipInnerShadows();

    QToolButton *btn_Addnew = new QToolButton;
    btn_Addnew->setIcon( QIcon(":/icons/dark/plus.svg") );

    LayoutSection *m_section = new LayoutSection(tr("Inner Shadows"), nullptr, true);
    m_section->addWidget(itemInnerShadows);
    m_section->setCollapsedState(true);
    m_section->addButton(btn_Addnew);

    this->connect(btn_Addnew, &QToolButton::clicked, itemInnerShadows, &ipInnerShadows::newShadow);
    this->connect(itemInnerShadows, &ipInnerShadows::sendCollapse, m_section, &LayoutSection::setCollapsedState);

    ui->layout->addWidget(m_section);
}

void ItemProperties::setupExportLevel()
{
    itemExportLevels = new ipExportLevels();

    QToolButton *btn_Addnew = new QToolButton;
    btn_Addnew->setIcon( QIcon(":/icons/dark/plus.svg") );

    LayoutSection *m_section = new LayoutSection(tr("Export"), nullptr, true);
    m_section->addWidget(itemExportLevels);
    m_section->setCollapsedState(true);
    m_section->addButton(btn_Addnew);

    this->connect(btn_Addnew, &QToolButton::clicked, itemExportLevels, &ipExportLevels::newExportLevel);
    this->connect(itemExportLevels, &ipExportLevels::sendCollapse, m_section, &LayoutSection::setCollapsedState);

    ui->layout->addWidget(m_section);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ItemProperties::setActiveItem(AbstractItemBase *item)
{
    itemGeometry->setActiveItem(item);
    itemFills->setActiveItem(item);
    itemStrokes->setActiveItem(item);
    itemShadows->setActiveItem(item);
    itemInnerShadows->setActiveItem(item);
    itemExportLevels->setActiveItem(item);
}
