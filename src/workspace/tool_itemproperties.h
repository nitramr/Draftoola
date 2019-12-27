#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QWidget>
#include "src/item/abstractitembase.h"

#include "tool_itemproperties/ip_geometry.h"
#include "tool_itemproperties/ip_fills.h"
#include "tool_itemproperties/ip_strokes.h"
#include "tool_itemproperties/ip_shadows.h"
#include "tool_itemproperties/ip_innershadows.h"
#include "tool_itemproperties/ip_exportlevel.h"

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
    void setActiveItem(AbstractItemBase *item);

signals:
    void exportItem(AbstractItemBase *item);

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
