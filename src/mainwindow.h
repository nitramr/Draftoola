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

    void tmpSetup();


public slots:
    void setActiveItems(QList<AbstractItemBase *> items);
    void addNewItem();

};

#endif // MAINWINDOW_H
