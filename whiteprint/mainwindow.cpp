#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "designer/canvas.h"
#include "item/warect.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Canvas * canvas = new Canvas();

    this->setCentralWidget(canvas);

	WARect * rect = new WARect(60,100);
	canvas->addItem(rect, 40,20);

}

MainWindow::~MainWindow()
{
    delete ui;
}
