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

#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QWidget>

#include <abstractitembase.h>
#include <ip_geometry.h>
#include <ip_fills.h>
#include <ip_strokes.h>
#include <ip_shadows.h>
#include <ip_innershadows.h>
#include <ip_exportlevel.h>

#include <QScrollArea>

namespace Ui {
class ItemProperties;
}

class ItemProperties : public QWidget
{
    Q_OBJECT

public:
    explicit ItemProperties(QScrollArea * container, QWidget *parent = nullptr);
    ~ItemProperties();

public slots:
    void setActiveItems(QList<AbstractItemBase *> items);

signals:
    void exportItem(AbstractItemBase *item);
    void itemsChanged();

private:
    Ui::ItemProperties *ui;
    QScrollArea * m_container;

    ipGeometry * itemGeometry;
    ipFills * itemFills;
    ipStrokes * itemStrokes;
    ipShadows * itemShadows;
    ipInnerShadows * itemInnerShadows;
    ipExportLevels * itemExportLevels;

    void setupGeometry();
    void setupFills();
    void setupStrokes();
    void setupShadows();
    void setupInnerShadows();
    void setupExportLevel();

};

#endif // ITEMPROPERTIES_H
