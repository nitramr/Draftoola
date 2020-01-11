#ifndef IP_FILLS_H
#define IP_FILLS_H

#include <QWidget>
#include <QList>
#include <abstractitembase.h>
#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <fills.h>
#include <propertyfill.h>

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
    void itemsChanged();

public slots:
    void newFill();

private slots:
    void updateItem();
};

#endif // IP_FILLS_H
