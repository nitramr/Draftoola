#include "propertyfill.h"
#include "ui_propertyfill.h"

#include <QPainter>
#include <QDebug>
#include "src/item/itemstruct.h"

PropertyFill::PropertyFill(QWidget *parent) : PropertyFill(Fills(), parent){}

PropertyFill::PropertyFill(Fills fill, QWidget *parent) : QWidget(parent),
ui(new Ui::propertyFill)
{
    ui->setupUi(this);

    m_colorPreview = QPixmap(ui->btn_color->iconSize());
    m_colorPreview.fill(Qt::black);
    ui->btn_color->setIcon(QIcon(m_colorPreview));

    // https://doc.qt.io/qt-5/qpainter.html#CompositionMode-enum
    ui->combo_blending->addItem("Normal", QVariant(QPainter::CompositionMode_SourceOver)); //0
    ui->combo_blending->addItem("Plus", QVariant(QPainter::CompositionMode_Plus)); //12
    ui->combo_blending->addItem("Multiply", QVariant(QPainter::CompositionMode_Multiply)); //13
    ui->combo_blending->addItem("Screen", QVariant(QPainter::CompositionMode_Screen)); //14
    ui->combo_blending->addItem("Overlay", QVariant(QPainter::CompositionMode_Overlay)); //15
    ui->combo_blending->addItem("Darken", QVariant(QPainter::CompositionMode_Darken)); //16
    ui->combo_blending->addItem("Lighten", QVariant(QPainter::CompositionMode_Lighten)); //17
    ui->combo_blending->addItem("Color Dodge", QVariant(QPainter::CompositionMode_ColorDodge)); //18
    ui->combo_blending->addItem("Color Burn", QVariant(QPainter::CompositionMode_ColorBurn)); //19
    ui->combo_blending->addItem("Hard Light", QVariant(QPainter::CompositionMode_HardLight)); //20
    ui->combo_blending->addItem("Soft Light", QVariant(QPainter::CompositionMode_SoftLight)); //21
    ui->combo_blending->addItem("Difference", QVariant(QPainter::CompositionMode_Difference)); //22
    ui->combo_blending->addItem("Exclusion", QVariant(QPainter::CompositionMode_Exclusion)); //23

    setFill(fill);
}

PropertyFill::~PropertyFill()
{
    delete ui;
}

void PropertyFill::setFill(Fills fill)
{
    disconnectSlots();

    m_fill = fill;
    ui->cb_active->setChecked(fill.isOn());
    ui->sb_opacity->setValue(fill.opacity());

    int indexMode = 0;
    for(int i = 0; i < ui->combo_blending->count(); i++){
        if(fill.blendMode() == static_cast<QPainter::CompositionMode>(ui->combo_blending->itemData(i).toInt())){
            indexMode = i;
            break;
        }
    }

    ui->combo_blending->setCurrentIndex(indexMode);

    drawFill(fill);

    connectSlots();
}

Fills PropertyFill::fill() const
{
    return m_fill;
}

void PropertyFill::drawFill(Fills fill)
{
    QPainter painter(&m_colorPreview);

    m_colorPreview.fill(Qt::white);
    painter.setOpacity(fill.opacity()/100.0);

    switch (fill.fillType()) {
    case FillType::Color:        
        painter.fillRect(m_colorPreview.rect(), QBrush(fill.color()));
        break;
    case FillType::Gradient:
        break;
    case FillType::Image:
        painter.drawPixmap(m_colorPreview.rect(), fill.pixmap(), fill.pixmap().rect());
        break;
    case FillType::Pattern:
        break;
    default:
        break;
    }

    ui->btn_color->setIcon(QIcon(m_colorPreview));
}

void PropertyFill::connectSlots()
{
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyFill::updateFill);
    connect(ui->sb_opacity, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertyFill::updateFill);
    connect(ui->combo_blending, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyFill::updateFill);
}

void PropertyFill::disconnectSlots()
{
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyFill::updateFill);
    disconnect(ui->sb_opacity, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertyFill::updateFill);
    disconnect(ui->combo_blending, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyFill::updateFill);
}

void PropertyFill::updateFill()
{
    m_fill.setIsOn(ui->cb_active->isChecked());
    m_fill.setOpacity(ui->sb_opacity->value());
    m_fill.setBlendMode(static_cast<QPainter::CompositionMode>(ui->combo_blending->currentData().toInt()) );

    // update preview
    drawFill(m_fill);

    emit hasChanged(true);
}
