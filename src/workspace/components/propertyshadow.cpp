#include "propertyshadow.h"
#include "ui_propertyshadow.h"

PropertyShadow::PropertyShadow(QWidget *parent) : PropertyShadow(Shadow(), parent){}

PropertyShadow::PropertyShadow(Shadow shadow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyShadow)
{
    ui->setupUi(this);

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::black);
    ui->btn_color->setIcon(pixmap);

    setShadow(shadow);
}


PropertyShadow::~PropertyShadow()
{
    delete ui;
}

void PropertyShadow::setShadow(Shadow shadow)
{
    disconnectSlots();

    m_shadow = shadow;
    ui->cb_active->setChecked(shadow.isOn());
    ui->sb_xOffset->setValue(shadow.offset().x());
    ui->sb_yOffset->setValue(shadow.offset().y());
    ui->sb_blur->setValue(shadow.radius());
    ui->sb_spread->setValue(shadow.spread());

    drawShadow(shadow);

    connectSlots();
}

Shadow PropertyShadow::shadow() const
{
    return m_shadow;
}

void PropertyShadow::drawShadow(Shadow shadow)
{
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), QBrush(shadow.color()));
    ui->btn_color->setIcon(QIcon(pixmap));

}

void PropertyShadow::connectSlots()
{
    connect(ui->btnDelete, &QToolButton::clicked, this, &PropertyShadow::removeClick);
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    connect(ui->sb_blur, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_spread, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_xOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_yOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
}

void PropertyShadow::disconnectSlots()
{
    disconnect(ui->btnDelete, &QToolButton::clicked, this, &PropertyShadow::removeClick);
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_blur, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_spread, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_xOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_yOffset, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
}

void PropertyShadow::updateShadow()
{
    m_shadow.setIsOn(ui->cb_active->isChecked());
    m_shadow.setOffset(QPointF(ui->sb_xOffset->value(), ui->sb_yOffset->value()));
    m_shadow.setRadius(ui->sb_blur->value());
    m_shadow.setSpread(ui->sb_spread->value());
    m_shadow.setBlendMode(m_shadow.blendMode()); // need real data
    m_shadow.setColor(m_shadow.color()); // need real data

    emit hasChanged(true);
}

void PropertyShadow::removeClick()
{
    emit remove(this);
}
