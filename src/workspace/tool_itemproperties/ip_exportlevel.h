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

#ifndef IP_EXPORT_H
#define IP_EXPORT_H

#include <QWidget>
#include <QList>
#include <abstractitembase.h>
#include <artboard.h>
#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <fills.h>
#include <propertyexportlevel.h>

namespace Ui {
class ipExportLevel;
}

class ipExportLevels : public QWidget
{
    Q_OBJECT

public:
    explicit ipExportLevels(QWidget *parent = nullptr);
    ~ipExportLevels();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipExportLevel *ui;

    AbstractItemBase *m_item;
    QList<PropertyExportLevel*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadExportLevels();
    void addExportLevel(PropertyExportLevel *propertyItem);
    void removeExportLevel(PropertyExportLevel *propertyItem);


signals:
    void sendCollapse(bool);
    void exportItem(AbstractItemBase *item);
    void itemsChanged();

public slots:
        void newExportLevel();

private slots:
        void updateItem();
        void doExport();
};

#endif // IP_EXPORT_H
