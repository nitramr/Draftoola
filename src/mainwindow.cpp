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

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <itempolygon.h>
#include <itemgroup.h>
#include <utilities.h>
#include <stroke.h>
#include <shadow.h>
#include <exportlevel.h>
#include <color.h>
#include <handleframe.h>
#include <stylefactory.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    QApplication::setStyle(new StyleFactory( QApplication::style()->objectName()));

	ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName());
    setUnifiedTitleAndToolBarOnMac(true);
    showMaximized();

    // inizialize widgets
    setupWorkspace();
    setupToolbar();


    // connect widgets
    connectSlots();

    int offsetX = 0;
    int offsetY = 0;

    // TODO: delete function for release
    for(int y = 0; y <10; y++){

        for(int x = 0; x <10; x++){
        tmpSetup(offsetX,offsetY);

        offsetX += 1000;

        }
        offsetX = 0;
        offsetY += 1000;
    }


}

MainWindow::~MainWindow()
{
	delete ui;

}

void MainWindow::setupWorkspace()
{
    QScrollArea * scrollProp = new QScrollArea();

    m_properties = new ItemProperties(scrollProp);
    m_outliner = new Outliner();

    m_canvas = new CanvasView();
    this->setCentralWidget(m_canvas);

    m_outlinerDock = new QDockWidget(tr("Outliner"));
    m_outlinerDock->setWidget(m_outliner);
    m_outlinerDock->setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_outlinerDock);

    m_propertiesDock = new QDockWidget("Properties");
    m_propertiesDock->setWidget(scrollProp);
    m_propertiesDock->setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea);
    this->addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);
}

void MainWindow::setupToolbar()
{

//    ui->mainToolBar->setFloatable(false);
//    ui->mainToolBar->setMovable(false);
//    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_toolArtboard = new QToolButton();
    m_toolArtboard->setIcon( QIcon(":/icons/dark/tools/presentation.svg") );
    m_toolArtboard->setText(tr("Artboard"));
    ui->mainToolBar->addWidget(m_toolArtboard);

    m_toolRectangle = new QToolButton();
    m_toolRectangle->setIcon( QIcon(":/icons/dark/tools/rectangle.svg") );
    m_toolRectangle->setText(tr("Rectangle"));
    ui->mainToolBar->addWidget(m_toolRectangle);
    connect(m_toolRectangle, &QToolButton::clicked, this, &MainWindow::addNewItem);

    m_toolOval = new QToolButton();
    m_toolOval->setIcon( QIcon(":/icons/dark/tools/ellipse.svg") );
    m_toolOval->setText(tr("Oval"));
    ui->mainToolBar->addWidget(m_toolOval);

    m_toolLine = new QToolButton();
    m_toolLine->setIcon( QIcon(":/icons/dark/tools/line.svg") );
    m_toolLine->setText(tr("Line"));
    ui->mainToolBar->addWidget(m_toolLine);

    m_toolTriangle = new QToolButton();
    m_toolTriangle->setIcon( QIcon(":/icons/dark/tools/triangle.svg") );
    m_toolTriangle->setText(tr("Triangle"));
    ui->mainToolBar->addWidget(m_toolTriangle);

    m_toolStar = new QToolButton();
    m_toolStar->setIcon( QIcon(":/icons/dark/tools/star.svg") );
    m_toolStar->setText(tr("Star"));
    ui->mainToolBar->addWidget(m_toolStar);

    m_toolPolygon = new QToolButton();
    m_toolPolygon->setIcon( QIcon(":/icons/dark/tools/pentagon.svg") );
    m_toolPolygon->setText(tr("Polygon"));
    ui->mainToolBar->addWidget(m_toolPolygon);

    m_toolPath = new QToolButton();
    m_toolPath->setIcon( QIcon(":/icons/dark/tools/fountain-pen-tip.svg") );
    m_toolPath->setText(tr("Vector"));
    ui->mainToolBar->addWidget(m_toolPath);

    m_toolText = new QToolButton();
    m_toolText->setIcon( QIcon(":/icons/dark/tools/format-textbox.svg") );
    m_toolText->setText(tr("Text"));
    ui->mainToolBar->addWidget(m_toolText);

    m_toolImage = new QToolButton();
    m_toolImage->setIcon( QIcon(":/icons/dark/tools/image.svg") );
    m_toolImage->setText(tr("Image"));
    ui->mainToolBar->addWidget(m_toolImage);



}

void MainWindow::connectSlots()
{
    connect(m_canvas->handleFrame(), &HandleFrame::sendActiveItems, this, &MainWindow::setActiveItems);
    connect(m_canvas, &CanvasView::itemsChanged, m_outliner, &Outliner::updateList);
    connect(m_canvas, &CanvasView::zoomChanged, this, &MainWindow::zoomHasChanged);
    connect(m_properties, &ItemProperties::itemsChanged, m_canvas->handleFrame(), &HandleFrame::frameToSelection);


    // signal to signal connection
    connect(m_properties, &ItemProperties::exportItem, [this](AbstractItemBase *item){
        emit m_scene->exportItem(item);
    });
}

void MainWindow::tmpSetup(int offsetX, int offsetY)
{
    // Gradients
    QLinearGradient lGradient(0,0,50,50);
    lGradient.setColorAt(0, Qt::white);
    lGradient.setColorAt(1, Qt::darkBlue);

    Gradient gradient("Gradient", lGradient);

    // Strokes
    Stroke strokeR("StrokeR", Color(128,208,23, 128),3, Stroke::Inner);
    Stroke stroke("Stroke", gradient,4, Stroke::Outer);
    stroke.setCapStyle(Qt::PenCapStyle::RoundCap);
    stroke.setStyle(Qt::PenStyle::DotLine);
    Stroke stroke3("Stroke3", QColor(128,208,23),2, Stroke::Center);

    // Shadows
    Shadow shadow = Shadow("Shadow", QColor(0,0,0,100), 0, QPointF(0,0),0);
    Shadow shadow2 = Shadow("Shadow2", QColor(255,0,0), 10, QPointF(0,0), 2);
    Shadow shadow3 = Shadow("Shadow3", QColor(0,0,0,255), 1, QPointF(0,0),0);


    // Fills - Image
//    QImage fillImage("sun.jpg");

    Fills fill("rect","sun.jpg");
    fill.setBlendMode(QPainter::CompositionMode_SourceOver);
//    fill.setFillMode(FillMode::Stretch);

    Fills fill2("oval", Color(255,0,0,128));
//    fill2.setStyle(Qt::Dense7Pattern);
//    fill2.setFillType(FillType::Pattern);

    Color c_black;
    Fills fill3("black", c_black);

    Fills fill4("Gradient", gradient);

    //Export Levels
    ExportLevel expLevel(0, 1);
    ExportLevel expLevel2(1, 2);
    ExportLevel expLevel3(2, 3);


    // Artboard
    Artboard *artboard = new Artboard("Artboard1");
    artboard->addExportLevel(expLevel);
    artboard->addExportLevel(expLevel2);
    //	artboard->setPos(20,20);
    m_canvas->addItem(artboard, 0+offsetX, 0+offsetY);
//    m_outliner->addNode(artboard);

//    QByteArray ar;
//    QDataStream stream(&ar, QIODevice::ReadWrite);
//    stream << artboard;
//    stream.device()->seek(0);

    // https://forum.qt.io/topic/78161/custom-class-serialize-with-qdatastream/2
//    QVariant TempVariant;
//    stream >> TempVariant;

    Artboard strGradient;
//    strTest = TempVariant.value<Shadow>(); // optional if QVariant is used

//    stream >> strGradient; // optional if QVariant is not used
 //   qDebug() << strGradient;


    // Object Ovals
    ItemOval *oval = new ItemOval();
    oval->setName("Oval1");
    oval->addFills(fill2);
//    oval->setRotation(45);
    oval->addStroke(stroke);
    oval->addShadow(shadow);
    oval->addShadow(shadow2);
    oval->addShadow(shadow3);
    oval->addExportLevel(expLevel);
    oval->addExportLevel(expLevel2);
    oval->addExportLevel(expLevel3);
    m_canvas->addItem(oval, 50,120, artboard);

    // Object Rects
    ItemRect *rect = new ItemRect(60,100);
//    rect->setTransform(QTransform().rotate(70, Qt::YAxis));
    rect->setName("Rect1");
    rect->setRadius(5,0,15,20);
//    rect->setRotation(45);
    rect->addStroke(strokeR);
    //	rect->addStroke(stroke);
    rect->addShadow(shadow);
    rect->addShadow(shadow2);
    rect->addInnerShadow(shadow3);
    rect->addFills(fill);
    m_canvas->addItem(rect, 10,10, artboard);

    ItemRect * rect2 = new ItemRect(10,10);
//	rect2->setRadius(0,0,15,0);
    rect2->setRotation(0);
    rect2->addFills(fill3);
    m_canvas->addItem(rect2, 30,10, oval);


    // Object Text
    ItemText *text = new ItemText("Hello World<br>second line");
    m_canvas->addItem(text, 100, 10, artboard);

    // Artboard
    Artboard *artboard2 = new Artboard("Artboard2");
    artboard2->addExportLevel(expLevel);
    //	artboard->setPos(20,20);
    m_canvas->addItem(artboard2, 400 +offsetX, 0 +offsetY);


    // Object Ovals
    ItemOval *oval2 = new ItemOval();
    oval2->setName("Oval2");
    oval2->addFills(fill4);
    m_canvas->addItem(oval2, 50,120, artboard2);

    ItemPolygon *star = new ItemPolygon(80,80, 5, true);
    star->setInnerRadius(0.5);
    star->addFills(Fills("color", Color("yellow",255,200,0)));
    star->addShadow(Shadow("shadow", Color("black",0,0,0), 10, QPointF(0,0)));
    m_canvas->addItem(star, 80,300, artboard);

    ItemPolygon *pentagon = new ItemPolygon(80,80, 5);
    pentagon->setInnerRadius(1);
    pentagon->addFills(Fills("color", Color("yellow",255,200,0)));
    pentagon->addShadow(Shadow("shadow", Color("black",0,0,0), 10, QPointF(0,0)));
    m_canvas->addItem(pentagon, 200,300, artboard);



    // Object Rects
    ItemRect *rectTrans = new ItemRect(70,140);
    rectTrans->setRadius(8);
    rectTrans->setTransform( QTransform().rotate(60, Qt::XAxis).rotate(45, Qt::ZAxis).translate(-rectTrans->rect().width()/2,-rectTrans->rect().height()/2) );
    rectTrans->setName("Rect Transformed");
    rectTrans->addShadow( Shadow("shadowSoft", Color("black",0,0,0, qRound(255*0.2) ), 16, QPointF(0,0)) );
    rectTrans->addShadow( Shadow("shadowCore", Color("black",0,0,0, qRound(255*0.5) ), 16, QPointF(0,0), -4) );
    m_canvas->addItem(rectTrans, 180,300, artboard2);


    QLinearGradient GrTrans(0,0,50,50);
    GrTrans.setColorAt(0, QColor(255,159,3));
    GrTrans.setColorAt(1, QColor(255,104,3, qRound(255*0.7) ));

    // Object Rects
    ItemRect *rectTrans2 = new ItemRect(70,140);
    rectTrans2->setRadius(8);
    rectTrans2->setTransform( QTransform().rotate(60, Qt::XAxis).rotate(45, Qt::ZAxis).translate(-rectTrans->rect().width()/2,-rectTrans->rect().height()/2) );
    rectTrans2->applyTransformation();
    rectTrans2->setName("Rect2 Transformed");
    rectTrans2->addFills( Fills("color", Gradient("GrTrans", GrTrans)) );
    m_canvas->addItem(rectTrans2, 180,290, artboard2);


//	stroke.setStrokePosition(StrokePosition::Outer);
//	ItemOval * ovalG = new ItemOval(50,50);
//	ovalG->addFills(Fills("oval", QColor(Qt::green)));
//	ovalG->addStroke(stroke);
//	ovalG->setParentItem(rect);


//        ItemRect * rectG = new ItemRect(50,60);
//        rectG->addFills(Fills("rect", QColor(Qt::blue)));
//        m_canvas->addItem(rectG, 60,0);

//        stroke.setStrokePosition(StrokePosition::Outer);
//        ItemOval * ovalG = new ItemOval(50,50);
//        ovalG->addFills(Fills("oval", QColor(Qt::green)));
//        ovalG->addStroke(stroke);
//        m_canvas->addItem(ovalG, 0,0);

//    	ItemGroup * group = new ItemGroup();
//    	group->addToGroup(rectG);
//    	group->addToGroup(ovalG);
//    	m_canvas->addItem(group, 20,280);
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void MainWindow::setActiveItems(QList<AbstractItemBase *> items)
{
    m_properties->setActiveItems(items);
}

void MainWindow::addNewItem()
{
    // Object Rects
    ItemRect *rect = new ItemRect(100,100);
    rect->setName("Rect");
    rect->addStroke(Stroke("tmpStroke", Color(Qt::darkGray)));
    rect->addFills(Fills("tmpFills", Color(Qt::lightGray)));
    m_canvas->addItem(rect, 0,0);
}

void MainWindow::zoomHasChanged(qreal zoomFactor)
{
    ui->statusBar->showMessage(QString::number(zoomFactor * 100) + "%" + "(" + QString::number(zoomFactor) + ")");
}
