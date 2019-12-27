#include "buttongroup.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

/***************************************************
 *
 * ButtonGroup Button
 *
 ***************************************************/

ButtonGroupButton::ButtonGroupButton(QWidget *parent) : QToolButton (parent)
{
    m_type = ButtonGroupButton::Type::normal;
}

void ButtonGroupButton::setButtonType(ButtonGroupButton::Type type)
{
    m_type = type;

}

ButtonGroupButton::Type ButtonGroupButton::buttonType()
{
    return m_type;
}

void ButtonGroupButton::paintEvent(QPaintEvent *event)
{
    if(buttonType() == ButtonGroupButton::Type::normal){
        QToolButton::paintEvent(event);
    }else{
        // Should be change look of button based on type
        QToolButton::paintEvent(event);
    }
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
}

void ButtonGroup::addButton(ButtonGroupButton *button, bool checked)
{
    button->setCheckable(true);
    button->setChecked(checked);
    bg->addButton(button);
    hl->addWidget(button);
}

