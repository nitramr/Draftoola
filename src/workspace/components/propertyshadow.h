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

#ifndef PROPERTYSHADOW_H
#define PROPERTYSHADOW_H

#include <QWidget>
#include <QPixmap>
#include <colordialog.h>

#include <shadow.h>

namespace Ui {
class propertyShadow;
}

class PropertyShadow : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyShadow(QWidget *parent = nullptr);
    explicit PropertyShadow(Shadow shadow, QWidget *parent = nullptr);
    ~PropertyShadow();

    void setShadow(Shadow shadow);
    Shadow shadow() const;

private:
    Ui::propertyShadow *ui;

    Shadow m_property;

    ColorDialog * m_colorDialog;

    void drawPreview(Shadow property);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateProperty();
    void updateColor();

signals:
    void hasChanged(bool);
    void remove(PropertyShadow*);
};

#endif // PROPERTYSHADOW_H
