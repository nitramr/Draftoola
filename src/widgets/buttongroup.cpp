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
}

void ButtonGroup::addButton(ButtonGroupButton *button, bool checked)
{
    button->setCheckable(true);
    button->setChecked(checked);
    bg->addButton(button);
    hl->addWidget(button);
}

