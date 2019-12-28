#ifndef IP_INNERSHADOWS_H
#define IP_INNERSHADOWS_H

#include <QWidget>
#include <QList>
#include "src/item/abstractitembase.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/item/shadow.h"
#include "../components/propertyshadow.h"

namespace Ui {
class ipShadows;
}

class ipInnerShadows : public QWidget
{
    Q_OBJECT

public:
    explicit ipInnerShadows(QWidget *parent = nullptr);
    ~ipInnerShadows();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipShadows *ui;

    ItemBase *m_item;
    QList<PropertyShadow*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadShadows();
    void addShadow(PropertyShadow *propertyItem);
    void removeShadow(PropertyShadow *propertyItem);

signals:
    void sendCollapse(bool);
    void enabled(bool);

public slots:
    void newShadow();

private slots:
    void updateItem();
};

#endif // IP_INNERSHADOWS_H
