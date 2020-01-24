#ifndef IP_EXPORT_H
#define IP_EXPORT_H

#include <QWidget>
#include <QList>
#include <abstractitembase.h>
#include <artboard.h>
#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <fills.h>
#include <propertyexportlevel.h>

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
    QList<PropertyExportLevel*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadExportLevels();
    void addExportLevel(PropertyExportLevel *propertyItem);
    void removeExportLevel(PropertyExportLevel *propertyItem);


signals:
    void sendCollapse(bool);
    void exportItem(AbstractItemBase *item);
    void itemsChanged();

public slots:
        void newExportLevel();

private slots:
        void updateItem();
        void doExport();
};

#endif // IP_EXPORT_H
