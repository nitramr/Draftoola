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

#ifndef PROPERTYEXPORTLEVEL_H
#define PROPERTYEXPORTLEVEL_H

#include <QWidget>
#include <QToolButton>

#include <exportlevel.h>

namespace Ui {
class propertyExportLevel;
}

class PropertyExportLevel : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyExportLevel(QWidget *parent = nullptr);
    explicit PropertyExportLevel(ExportLevel exportLevel, QWidget *parent = nullptr);
    ~PropertyExportLevel();

    void setExportLevel(ExportLevel exportLevel);
    ExportLevel exportLevel() const;

private:
    Ui::propertyExportLevel *ui;

    ExportLevel m_exportLevel;

    void drawFill(ExportLevel exportLevel);
    void connectSlots();
    void disconnectSlots();

signals:
    void remove(PropertyExportLevel*);
    void hasChanged(bool);

private slots:
    void removeClick();
    void updateFill();

};

#endif // PROPERTYEXPORTLEVEL_H
