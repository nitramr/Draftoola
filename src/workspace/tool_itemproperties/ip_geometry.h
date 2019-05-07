#ifndef IP_GEOMETRY_H
#define IP_GEOMETRY_H

#include <QWidget>

#include "src/item/abstractitembase.h"
#include "src/item/artboard.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"

namespace Ui {
class ip_geometry;
}

class ipGeometry : public QWidget
{
    Q_OBJECT

public:
    explicit ipGeometry(QWidget *parent = nullptr);
    ~ipGeometry();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ip_geometry *ui;

    AbstractItemBase *m_item;

    void loadProperties();
    void loadGeometry();
    void resetItems();
    void unloadItems();

private slots:
    void updateItem();

signals:
    void hasChanged(bool);
};

#endif // IP_GEOMETRY_H
