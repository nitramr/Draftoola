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

    if(fill.fillType() == FillType::Color){

        int opacity = static_cast<int>(fill.color().alphaF() * 100);

        ui->sb_opacity->setValue(opacity);
    }else ui->sb_opacity->setValue(fill.opacity());

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

    switch (fill.fillType()) {
    case FillType::Color:
        m_colorPreview.fill(Qt::white);
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
}

void PropertyFill::disconnectSlots()
{
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyFill::updateFill);
    disconnect(ui->sb_opacity, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertyFill::updateFill);
}

void PropertyFill::updateFill()
{
    m_fill.setIsOn(ui->cb_active->isChecked());
    m_fill.setOpacity(ui->sb_opacity->value());
    emit hasChanged(true);
}
