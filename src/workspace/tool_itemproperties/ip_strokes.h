#ifndef IP_STROKES_H
#define IP_STROKES_H

#include <QWidget>
#include <QList>
#include <abstractitembase.h>
#include <itembase.h>
#include <itemrect.h>
#include <itemoval.h>
#include <itemtext.h>
#include <stroke.h>
#include <propertystroke.h>

namespace Ui {
class ipStrokes;
}

class ipStrokes : public QWidget
{
    Q_OBJECT

public:
    explicit ipStrokes(QWidget *parent = nullptr);
    ~ipStrokes();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipStrokes *ui;

    ItemBase *m_item;
    QList<PropertyStroke*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadStrokes();
    void addStroke(PropertyStroke *propertyItem);
    void removeStroke(PropertyStroke *propertyItem);

signals:
    void sendCollapse(bool);
    void enabled(bool);
    void itemsChanged();

public slots:
    void newStroke();

private slots:
    void updateItem();
};

#endif // IP_STROKES_H
