#include "propertyshadow.h"
#include "ui_propertyshadow.h"

PropertyShadow::PropertyShadow(QWidget *parent) : PropertyShadow(Shadow(), parent){}

PropertyShadow::PropertyShadow(Shadow shadow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyShadow)
{
    ui->setupUi(this);

    m_colorPreview = QPixmap(ui->btn_color->iconSize());
    m_colorPreview.fill(Qt::black);
    ui->btn_color->setIcon(QIcon(m_colorPreview));

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
    qDebug() << "Shadow ID" << m_shadow.ID();

    return m_shadow;
}

void PropertyShadow::drawShadow(Shadow shadow)
{
    QPainter painter(&m_colorPreview);
    painter.fillRect(m_colorPreview.rect(), QBrush(Qt::white));
    painter.fillRect(m_colorPreview.rect(), QBrush(shadow.color()));
    ui->btn_color->setIcon(QIcon(m_colorPreview));
}

void PropertyShadow::connectSlots()
{
    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    connect(ui->sb_blur, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_spread, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_xOffset, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    connect(ui->sb_yOffset, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
}

void PropertyShadow::disconnectSlots()
{
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_blur, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_spread, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_xOffset, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
    disconnect(ui->sb_yOffset, qOverload<double>(&IntelligentSpinBox::valueChanged), this, &PropertyShadow::updateShadow);
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
