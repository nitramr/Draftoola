#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "item/warect.h"
#include "item/waoval.h"
#include "item/watext.h"
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
	artboard->setPos(20,20);
	m_canvas->addItem(artboard);
	m_outliner->addNode(artboard);

	WARect * rect = new WARect(60,100);
	rect->setFills(Fills("rect", QColor(Qt::yellow)));
	m_canvas->addItem(rect, 10,10);

	WAOval * oval = new WAOval(60,80);
	oval->setFills(Fills("oval", QColor(Qt::red)));
	m_canvas->addItem(oval, 40,180);

	WAText * text = new WAText("Hello World");
	m_canvas->addItem(text, 100, 10);

	connect(m_canvas->view()->handleFrame(), SIGNAL(emitActiveItem(ItemBase*)), this, SLOT(setActiveItem(ItemBase*)));

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

void MainWindow::setActiveItem(ItemBase *item)
{
    m_properties->setActiveItem(item);
}
