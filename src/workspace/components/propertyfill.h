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

#ifndef PROPERTYFILL_H
#define PROPERTYFILL_H

#include <QWidget>
#include <QPixmap>

#include <fills.h>
#include <colordialog.h>

namespace Ui {
class propertyFill;
}

class PropertyFill : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyFill(QWidget *parent = nullptr);
    explicit PropertyFill(Fills fill, QWidget *parent = nullptr);
    ~PropertyFill();

    void setFill(Fills fill);
    Fills fill() const;

private:
    Ui::propertyFill *ui;

    Fills m_property;

    ColorDialog * m_colorDialog;

    void drawFill(Fills property);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateProperty();
    void updateColor();
    void updateOpacity();

signals:
    void hasChanged(bool);
    void remove(PropertyFill*);

};

#endif // PROPERTYFILL_H
