#include "intelligentspinbox.h"
#include <QDebug>
#include <QScriptEngine>

IntelligentSpinBox::IntelligentSpinBox(QWidget *parent) : QDoubleSpinBox (parent)
{
    QRegExp rx("(\\d+\\s*|[+\\-*\\/^%,]\\s*)*");
//    QRegExp rx("(\\d+[+\\-*\\/^%,])*(\\d+)");
//    QRegExp rx("((\\d+,?)\\s*(px\\s*)?([+\\-*\\/^%,]\\s*)?(px\\s*)?)");
    validator = new QRegExpValidator(rx, this);

    setDecimals(1);

//    don't support handling of suffix yet.
//    setSuffix("px");


}

QValidator::State IntelligentSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

double IntelligentSpinBox::valueFromText(const QString &text) const
{
    QString expression_string(text);
    expression_string = expression_string.replace(",", ".");
    QScriptEngine expression;

    return expression.evaluate(expression_string).toNumber();
}
