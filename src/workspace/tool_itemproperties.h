#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QWidget>

#include <abstractitembase.h>
#include <ip_geometry.h>
#include <ip_fills.h>
#include <ip_strokes.h>
#include <ip_shadows.h>
#include <ip_innershadows.h>
#include <ip_exportlevel.h>

#include <QScrollArea>

namespace Ui {
class ItemProperties;
}

class ItemProperties : public QWidget
{
    Q_OBJECT

public:
    explicit ItemProperties(QScrollArea * container, QWidget *parent = nullptr);
    ~ItemProperties();

public slots:
    void setActiveItems(QList<AbstractItemBase *> items);

signals:
    void exportItem(AbstractItemBase *item);
    void itemsChanged();

private:
    Ui::ItemProperties *ui;
    QScrollArea * m_container;

    ipGeometry * itemGeometry;
    ipFills * itemFills;
    ipStrokes * itemStrokes;
    ipShadows * itemShadows;
    ipInnerShadows * itemInnerShadows;
    ipExportLevels * itemExportLevels;

    void setupGeometry();
    void setupFills();
    void setupStrokes();
    void setupShadows();
    void setupInnerShadows();
    void setupExportLevel();

};

#endif // ITEMPROPERTIES_H
