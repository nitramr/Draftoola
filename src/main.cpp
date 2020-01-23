#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Draftoola Studio");
    QCoreApplication::setApplicationVersion("0.1 alpha");
    QCoreApplication::setOrganizationName("Draftoola Development Team");

    qRegisterMetaTypeStreamOperators<AbstractItemProperty>("AbstractItemProperty");

    qRegisterMetaType<Shadow>("Shadow");
    qRegisterMetaTypeStreamOperators<Shadow>("Shadow");

    qRegisterMetaType<ExportLevel>("ExportLevel");
    qRegisterMetaType<Fills>("Fills");
    qRegisterMetaType<Stroke>("Stroke");
    qRegisterMetaType<Gradient>("Gradient");
    qRegisterMetaType<Color>("Color");
//    qRegisterMetaType<AbstractItemBase>("AbstractItemBase");

    MainWindow w;
    w.show();

    return a.exec();
}
