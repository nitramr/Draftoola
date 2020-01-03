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

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::black);
    ui->btn_color->setIcon(pixmap);

    // https://doc.qt.io/qt-5/qpainter.html#CompositionMode-enum
    ui->combo_blending->addItem(tr("Normal"), QVariant(QPainter::CompositionMode_SourceOver)); //0

    ui->combo_blending->addItem(tr("Darken"), QVariant(QPainter::CompositionMode_Darken)); //16
    ui->combo_blending->addItem(tr("Multiply"), QVariant(QPainter::CompositionMode_Multiply)); //13
    ui->combo_blending->addItem(tr("Color Burn"), QVariant(QPainter::CompositionMode_ColorBurn)); //19

    ui->combo_blending->addItem(tr("Lighten"), QVariant(QPainter::CompositionMode_Lighten)); //17
    ui->combo_blending->addItem(tr("Screen"), QVariant(QPainter::CompositionMode_Screen)); //14
    ui->combo_blending->addItem(tr("Color Dodge"), QVariant(QPainter::CompositionMode_ColorDodge)); //18

    ui->combo_blending->addItem(tr("Overlay"), QVariant(QPainter::CompositionMode_Overlay)); //15
    ui->combo_blending->addItem(tr("Soft Light"), QVariant(QPainter::CompositionMode_SoftLight)); //21
    ui->combo_blending->addItem(tr("Hard Light"), QVariant(QPainter::CompositionMode_HardLight)); //20
    ui->combo_blending->addItem(tr("Difference"), QVariant(QPainter::CompositionMode_Difference)); //22
    ui->combo_blending->addItem(tr("Exclusion"), QVariant(QPainter::CompositionMode_Exclusion)); //23

    ui->combo_blending->addItem(tr("Plus"), QVariant(QPainter::CompositionMode_Plus)); //12


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
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setOpacity(fill.opacity()/100.0);

    switch (fill.fillType()) {
    case FillType::Color:{
        painter.fillRect(pixmap.rect(), QBrush(fill.color()));
        break;
    }
    case FillType::Gradient:
        break;
    case FillType::Image:
        painter.drawPixmap(pixmap.rect(), fill.pixmap(), fill.pixmap().rect());
        break;
    case FillType::Pattern:
        break;
    default:
        break;
    }

    ui->btn_color->setIcon(pixmap);
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
