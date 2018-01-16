#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "item/itembase.h"
#include "item/warect.h"
#include "item/waoval.h"
#include "item/watext.h"
#include "item/wagroup.h"
#include "designer/handleframe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_properties = new ItemProperties();
    m_outliner = new Outliner();

	m_canvas = new Canvas();
	this->setCentralWidget(m_canvas);

    m_outlinerDock = new QDockWidget(tr("Outliner"));
    m_outlinerDock->setWidget(m_outliner);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_outlinerDock);

    m_propertiesDock = new QDockWidget("Properties");
    m_propertiesDock->setWidget(m_properties);
    this->addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);



	Artboard *artboard = new Artboard("Artboard1");
//	artboard->setPos(20,20);
	m_canvas->addItem(artboard);
	m_outliner->addNode(artboard);

	WARect * rect = new WARect(60,100);
	rect->setFills(Fills("rect", QColor(Qt::yellow)));
	rect->setRadius(20);
	rect->setRotation(45);
	m_canvas->addItem(rect, 10,10);

	WAOval * oval = new WAOval(60,80);
	oval->setFills(Fills("oval", QColor(Qt::red)));
	m_canvas->addItem(oval, 20,120);

	WAText * text = new WAText("Hello World");
	m_canvas->addItem(text, 100, 10);

	WARect * rectG = new WARect(50,50);
	rectG->setFills(Fills("rect", QColor(Qt::blue)));
	m_canvas->addItem(rectG, 60,0);

	Stroke stroke("TestEllipseStroke", QBrush(QColor(128,208,23)),1);

	WAOval * ovalG = new WAOval(50,50);
	ovalG->setFills(Fills("oval", QColor(Qt::green)));
	ovalG->setStroke(stroke);
	ovalG->setStrokePosition(StrokePosition::Inner);
	m_canvas->addItem(ovalG, 0,0);

	WAGroup * group = new WAGroup();
	group->addToGroup(rectG);
	group->addToGroup(ovalG);
	m_canvas->addItem(group, 20,280);


	connect(m_canvas->view()->handleFrame(), SIGNAL(emitActiveItem(QGraphicsItem*)), this, SLOT(setActiveItem(QGraphicsItem*)));

}

MainWindow::~MainWindow()
{
    delete ui;

}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void MainWindow::setActiveItem(QGraphicsItem *item)
{
    m_properties->setActiveItem(item);
}
