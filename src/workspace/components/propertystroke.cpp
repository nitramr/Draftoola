#include "propertystroke.h"
#include "ui_propertystroke.h"

#include <QPainter>
#include <QDebug>
#include <itemstruct.h>

PropertyStroke::PropertyStroke(QWidget *parent) : PropertyStroke(Stroke("tmpFill", QColor(0,0,0) ), parent){}

PropertyStroke::PropertyStroke(Stroke stroke, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyStroke)
{
    ui->setupUi(this);

    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::black);
    ui->btn_color->setIcon(pixmap);

    btn_center = new ButtonGroupButton();
    btn_center->setText("C");
    btn_center->setButtonType(ButtonGroupButton::Type::middle);
    btn_outer = new ButtonGroupButton();
    btn_outer->setText("O");
    btn_outer->setButtonType(ButtonGroupButton::Type::left);
    btn_inner = new ButtonGroupButton();
    btn_inner->setText("I");
    btn_inner->setButtonType(ButtonGroupButton::Type::right);

    m_position = new ButtonGroup();
    m_position->addButton(btn_outer, false);
    m_position->addButton(btn_center, true);
    m_position->addButton(btn_inner, false);

    ui->lyt_position->insertWidget(0, m_position);

    setStroke(stroke);
}

PropertyStroke::~PropertyStroke()
{
    delete ui;
}

void PropertyStroke::setStroke(Stroke stroke)
{
    disconnectSlots();

    m_stroke = stroke;
    ui->cb_active->setChecked(stroke.isOn());
    ui->sb_width->setValue(stroke.widthF());

    switch(stroke.strokePosition()){
    case Stroke::Center:
            btn_center->setChecked(true);
        break;
    case Stroke::Outer:
            btn_outer->setChecked(true);
        break;
    case Stroke::Inner:
            btn_inner->setChecked(true);
        break;

    }

    drawStroke(stroke);

    connectSlots();
}

Stroke PropertyStroke::stroke() const
{
    return m_stroke;
}


void PropertyStroke::drawStroke(Stroke stroke)
{
    QPixmap pixmap(ui->btn_color->iconSize());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), stroke.brush());
    ui->btn_color->setIcon(QIcon(pixmap));

}

void PropertyStroke::connectSlots()
{
    connect(ui->btnDelete, &QToolButton::clicked, this, &PropertyStroke::removeClick);

//    connect(ui->btnDelete, &QToolButton::clicked, [this]{
//        emit remove(this);
//    });

    connect(ui->cb_active, &QCheckBox::clicked, this, &PropertyStroke::updateStroke);
    connect(ui->sb_width, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyStroke::updateStroke);
    connect(btn_center, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    connect(btn_inner, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    connect(btn_outer, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
}

void PropertyStroke::disconnectSlots()
{
    disconnect(ui->btnDelete, &QToolButton::clicked, this, &PropertyStroke::removeClick);
    disconnect(ui->cb_active, &QCheckBox::clicked, this, &PropertyStroke::updateStroke);
    disconnect(ui->sb_width, QOverload<double>::of(&IntelligentSpinBox::valueChanged), this, &PropertyStroke::updateStroke);
    disconnect(btn_center, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    disconnect(btn_inner, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
    disconnect(btn_outer, &QToolButton::clicked, this, &PropertyStroke::updateStroke);
}

void PropertyStroke::updateStroke()
{
    m_stroke.setIsOn(ui->cb_active->isChecked());
    m_stroke.setBlendMode(m_stroke.blendMode());  // need real data
    m_stroke.setBrush(m_stroke.brush()); // need real data (use brush for solid color too)
    m_stroke.setWidthF(ui->sb_width->value());

    if(btn_outer->isChecked()){
        m_stroke.setStrokePosition(Stroke::Outer);
    }else if(btn_inner->isChecked()){
        m_stroke.setStrokePosition(Stroke::Inner);
    }else m_stroke.setStrokePosition(Stroke::Center);


    emit hasChanged(true);
}

void PropertyStroke::removeClick()
{
    emit remove(this);
}
