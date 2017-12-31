#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "designer/canvas.h"
#include "item/warect.h"
#include "item/waoval.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Canvas * canvas = new Canvas();

    this->setCentralWidget(canvas);

	WARect * rect = new WARect(60,100);
	rect->setFills(Fills("rect", QColor(Qt::yellow)));
	canvas->addItem(rect, 40,20);


	WAOval * oval = new WAOval(60,80);
	oval->setFills(Fills("oval", QColor(Qt::red)));
	canvas->addItem(oval, 40,180);

}

MainWindow::~MainWindow()
{
    delete ui;
}
