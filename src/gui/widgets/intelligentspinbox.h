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

#ifndef INTELLIGENTSPINBOX_H
#define INTELLIGENTSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLineEdit>

class IntelligentSpinBox : public QDoubleSpinBox
{
public:
    IntelligentSpinBox(QWidget *parent = nullptr);

private:
//    double dbl_value;
//    QString str_value;
//    QLineEdit *lineEdit;
    QRegExpValidator *validator;

protected:
    QValidator::State validate(QString &text, int &pos) const;
    double valueFromText(const QString &text) const;
};

#endif // INTELLIGENTSPINBOX_H
