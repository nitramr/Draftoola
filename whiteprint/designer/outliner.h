#ifndef OUTLINER_H
#define OUTLINER_H

#include <QWidget>
#include <QGraphicsItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "whiteprint/item/itembase.h"

namespace Ui {
class Outliner;
}

class Outliner : public QWidget
{
    Q_OBJECT

public:
    explicit Outliner(QWidget *parent = 0);
    ~Outliner();

    void addNode(ItemBase * node);

private:
    Ui::Outliner *ui;
};

#endif // OUTLINER_H
