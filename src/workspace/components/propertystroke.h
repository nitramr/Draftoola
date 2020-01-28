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

#ifndef PROPERTYSTROKE_H
#define PROPERTYSTROKE_H

#include <QWidget>
#include <QPixmap>

#include <buttongroup.h>
#include <stroke.h>
#include <colordialog.h>

namespace Ui {
class propertyStroke;
}

class PropertyStroke : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyStroke(QWidget *parent = nullptr);
    explicit PropertyStroke(Stroke stroke, QWidget *parent = nullptr);
    ~PropertyStroke();

    void setStroke(Stroke stroke);
    Stroke stroke() const;

private:
    Ui::propertyStroke *ui;

    Stroke m_property;
    ColorDialog * m_colorDialog;

    ButtonGroup *m_position;
    ButtonGroupButton * btn_center;
    ButtonGroupButton * btn_outer;
    ButtonGroupButton * btn_inner;

    void drawPreview(Stroke property);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateProperty();
    void updateColor();

signals:
    void hasChanged(bool);
    void remove(PropertyStroke*);
};

#endif // PROPERTYSTROKE_H
