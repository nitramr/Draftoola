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

#ifndef IP_GEOMETRY_H
#define IP_GEOMETRY_H

#include <QWidget>

#include "src/item/abstractitembase.h"
#include "src/item/artboard.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/widgets/buttongroup.h"

namespace Ui {
class ip_geometry;
}

class ipGeometry : public QWidget
{
    Q_OBJECT

public:
    explicit ipGeometry(QWidget *parent = nullptr);
    ~ipGeometry();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ip_geometry *ui;

    AbstractItemBase *m_item;
    ButtonGroup *btnGroup;
    ButtonGroupButton *btnFree;
    ButtonGroupButton *btnFixedHeight;
    ButtonGroupButton *btnFixedWidth;
    ButtonGroupButton *btnFixedSize;

    void loadProperties();
    void loadGeometry();
    void resetItems();
    void unloadItems();
    void connectSlots();
    void disconnectSlots();
    void updateFrameState(AbstractItemBase::FrameType frameType);

private slots:
    void updateItem();

signals:
    void itemsChanged();
};

#endif // IP_GEOMETRY_H
