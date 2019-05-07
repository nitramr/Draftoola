#include "stylefactory.h"
#include <QtWidgets>

StyleFactory::StyleFactory(const QString name) : QProxyStyle(QStyleFactory::create(name))
{

}

void StyleFactory::drawControl(ControlElement control, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
//    case CE_PushButtonLabel:
//        {
//            QStyleOptionButton myButtonOption;
//            const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
//            if (buttonOption) {
//                myButtonOption = *buttonOption;
//                if (myButtonOption.palette.currentColorGroup()
//                        != QPalette::Disabled) {
//                    if (myButtonOption.state & (State_Sunken | State_On)) {
//                        myButtonOption.palette.setBrush(QPalette::ButtonText,
//                                myButtonOption.palette.brightText());
//                    }
//                }
//            }
//            QProxyStyle::drawControl(control, &myButtonOption, painter, widget);
//        }
//        break;
    default:
        QProxyStyle::drawControl(control, option, painter, widget);
    }
}

void StyleFactory::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
    case CC_ToolButton:
    {
        QStyleOptionToolButton myButtonOption;
        const QStyleOptionToolButton *buttonOption = qstyleoption_cast<const QStyleOptionToolButton *>(option);
        if (buttonOption) {
            myButtonOption = *buttonOption;
//            if (myButtonOption.palette.currentColorGroup() != QPalette::Disabled) {
//                if (myButtonOption.state & (State_Sunken | State_On)) {
//                    myButtonOption.palette.setBrush(QPalette::ButtonText,
//                            myButtonOption.palette.brightText());
//                }
//            }

        }

        QProxyStyle::drawComplexControl(control, &myButtonOption, painter, widget);
    }
        break;
    default:
        QProxyStyle::drawComplexControl(control, option, painter, widget);
    }
}
