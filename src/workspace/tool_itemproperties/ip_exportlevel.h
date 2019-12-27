#ifndef IP_EXPORT_H
#define IP_EXPORT_H

#include <QWidget>
#include <QList>
#include "src/item/abstractitembase.h"
#include "src/item/artboard.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/item/fills.h"
#include "../components/propertyexportlevel.h"

namespace Ui {
class ipExportLevel;
}

class ipExportLevels : public QWidget
{
    Q_OBJECT

public:
    explicit ipExportLevels(QWidget *parent = nullptr);
    ~ipExportLevels();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipExportLevel *ui;

    AbstractItemBase *m_item;
    QList<PropertyExportLevel*>*m_exportLevelItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadExportLevels();
    void addExportLevel(PropertyExportLevel *propertyItem);
    void removeExportLevel(PropertyExportLevel *propertyItem);


signals:
    void sendCollapse(bool);
    void exportItem(AbstractItemBase *item);

public slots:
        void newExportLevel();

private slots:
        void updateItem();
        void doExport();
};

#endif // IP_EXPORT_H
