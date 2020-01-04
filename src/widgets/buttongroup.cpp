#include "buttongroup.h"

#include <QPainter>
#include <QStyleOptionComboBox>

/***************************************************
 *
 * ButtonGroup Button
 *
 ***************************************************/

ButtonGroupButton::ButtonGroupButton(QWidget *parent) : QToolButton (parent)
{
    setButtonType(ButtonGroupButton::Type::normal);
}

void ButtonGroupButton::setButtonType(ButtonGroupButton::Type type)
{
    m_type = type;
}

ButtonGroupButton::Type ButtonGroupButton::buttonType()
{
    return m_type;
}

void ButtonGroupButton::setData(QVariant data)
{
    m_data = data;
}

QVariant ButtonGroupButton::data()
{
    return m_data;
}

void ButtonGroupButton::paintEvent(QPaintEvent *event)
{
    if(buttonType() == ButtonGroupButton::Type::normal){
        QToolButton::paintEvent(event);
    }else{
        // Should be change look of button based on type
        QToolButton::paintEvent(event);
    }

//    QStyleOptionButton option;
//        option.initFrom(this);
//        option.state = isDown() ? QStyle::State_Sunken : QStyle::State_Raised;
//        //if (isDefault())
//            option.features |= QStyleOptionButton::DefaultButton;
//        option.text = text();
//        option.icon = icon();

//        QStylePainter painter(this);
//        painter.drawControl(QStyle::CE_PushButton, &option, &painter, this);


}



/***************************************************
 *
 * ButtonGroup
 *
 ***************************************************/

ButtonGroup::ButtonGroup(QWidget *parent): QWidget(parent)
{
    bg = new QButtonGroup;

    hl = new QHBoxLayout;
    hl->setContentsMargins(0, 0, 0, 0);
    hl->setMargin(0);
    hl->setSpacing(0);

    setLayout(hl);

    connect(bg, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonPressed),
        [=](QAbstractButton *button){ emit buttonPressed(button); });
    connect(bg, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
        [=](QAbstractButton *button){ emit buttonClicked(button); });
}

void ButtonGroup::addButton(ButtonGroupButton *button, bool checked)
{
    button->setCheckable(true);
    button->setChecked(checked);
    bg->addButton(button);
    hl->addWidget(button);
}

QAbstractButton *ButtonGroup::checkedButton() const
{
    return bg->checkedButton();
}

QList<QAbstractButton *> ButtonGroup::buttons() const
{
    return bg->buttons();
}

