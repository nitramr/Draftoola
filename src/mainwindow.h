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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "workspace/tool_itemproperties.h"
#include "workspace/tool_outliner.h"
//#include "designer/canvas.h"
//#include "designer/canvasframe.h"
#include "item/itembase.h"
#include "item/artboard.h"
#include "designer/canvasscene.h"
#include "designer/canvasview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    Outliner * m_outliner;
    ItemProperties * m_properties;
    CanvasView * m_canvas;
    CanvasScene * m_scene;
    QDockWidget * m_outlinerDock;
    QDockWidget * m_propertiesDock;

    // Tools
    QToolButton *m_toolRectangle;
    QToolButton *m_toolOval;
    QToolButton *m_toolText;
    QToolButton *m_toolLine;
    QToolButton *m_toolTriangle;
    QToolButton *m_toolStar;
    QToolButton *m_toolPolygon;
    QToolButton *m_toolPath;
    QToolButton *m_toolImage;
    QToolButton *m_toolArtboard;

    void setupWorkspace();
    void setupToolbar();

    void connectSlots();

    void tmpSetup(int offsetX, int offsetY);


public slots:
    void setActiveItems(QList<AbstractItemBase *> items);
    void addNewItem();
    void zoomHasChanged(qreal zoomFactor);

};

#endif // MAINWINDOW_H
