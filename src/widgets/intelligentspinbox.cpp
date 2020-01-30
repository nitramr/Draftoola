/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "intelligentspinbox.h"
#include <QDebug>
#include <QScriptEngine>

IntelligentSpinBox::IntelligentSpinBox(QWidget *parent) : QDoubleSpinBox (parent)
{
    /*

      Left part: match negative or positive number with optional comma
      -?\d+(?:(?:\,|\.)\d+(?:\d+)*)?

      Mid part: matches an arithmetic operator inclusive optional spaces
      (?:\s*[-+/\*]\s*

      Right part: match negative or positive number with optional comma
      -?\d+(?:(?:\,|\.)\d+(?:\d+)*)?)*

      Mid and right part are grouped so that they can be unlimited included in formula

     */

    QRegExp rx("-?\\d+(?:(?:\\,|\\.)\\d+(?:\\d+)*)?(?:\\s*[-+\\/\\*]\\s*-?\\d+(?:(?:\\,|\\.)\\d+(?:\\d+)*)?)*");
    validator = new QRegExpValidator(rx, this);

    setDecimals(1);
    setKeyboardTracking(false); // deactivate value change on each key press


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
