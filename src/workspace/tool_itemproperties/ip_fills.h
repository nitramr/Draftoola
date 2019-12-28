#ifndef IP_FILLS_H
#define IP_FILLS_H

#include <QWidget>
#include <QList>
#include "src/item/abstractitembase.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/item/fills.h"
#include "../components/propertyfill.h"

namespace Ui {
class ipFills;
}

class ipFills : public QWidget
{
    Q_OBJECT

public:
    explicit ipFills(QWidget *parent = nullptr);
    ~ipFills();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipFills *ui;

    ItemBase *m_item;
    QList<PropertyFill*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadFills();
    void addFill(PropertyFill *propertyItem);
    void removeFill(PropertyFill *propertyItem);

signals:
    void sendCollapse(bool);
    void enabled(bool);

public slots:
    void newFill();

private slots:
    void updateItem();
};

#endif // IP_FILLS_H
