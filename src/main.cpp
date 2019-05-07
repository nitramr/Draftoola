#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Shadow>("Shadow");
    qRegisterMetaType<ExportLevel>("ExportLevel");
    qRegisterMetaType<Fills>("Fills");
    qRegisterMetaType<Stroke>("Stroke");
    qRegisterMetaType<Gradient>("Gradient");

    MainWindow w;
    w.show();

    return a.exec();
}
