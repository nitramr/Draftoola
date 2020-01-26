/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

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

#ifndef COLORINPUT_H
#define COLORINPUT_H

#include <QWidget>

namespace Ui {
class ColorInput;
}

class ColorInput : public QWidget
{
    Q_OBJECT

public:
    explicit ColorInput(QWidget *parent = nullptr);
    ~ColorInput();

private:
    Ui::ColorInput *ui;

    void connectSlots();
    void disconnectSlots();

public slots:
    void setColor(const QColor color, qreal alpha);

private slots:
    void updateColor();

signals:
    void colorChanged(QColor color, qreal alpha);

};

#endif // COLORINPUT_H
