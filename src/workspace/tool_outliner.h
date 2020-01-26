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

#ifndef OUTLINER_H
#define OUTLINER_H

#include <QWidget>
#include <QGraphicsItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <abstractitembase.h>

namespace Ui {
class Outliner;
}

class Outliner : public QWidget
{
    Q_OBJECT

public:
    explicit Outliner(QWidget *parent = nullptr);
    ~Outliner();

public slots:
    void updateList();

private:
    Ui::Outliner *ui;
};

#endif // OUTLINER_H
