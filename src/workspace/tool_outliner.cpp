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

#include "tool_outliner.h"
#include "ui_tool_outliner.h"

#include <artboard.h>
#include <canvasview.h>

#include <QDebug>

Outliner::Outliner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outliner)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Artboards");
}

Outliner::~Outliner()
{
    delete ui;
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void Outliner::updateList()
{
    CanvasView *canvas = static_cast<CanvasView*>(sender());

    if(canvas){

        ui->treeWidget->clear();

        foreach(Artboard* artboard, canvas->artboardList()){
            QTreeWidgetItem * twi = new QTreeWidgetItem();
            twi->setText(0, artboard->name());

            foreach(AbstractItemBase *item, artboard->childItems()){
                QTreeWidgetItem * twc = new QTreeWidgetItem();
                twc->setText(0, item->name());
                twi->addChild(twc);

            }
            ui->treeWidget->addTopLevelItem(twi);
        }

    }

}
