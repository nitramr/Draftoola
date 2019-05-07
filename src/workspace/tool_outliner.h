#ifndef OUTLINER_H
#define OUTLINER_H

#include <QWidget>
#include <QGraphicsItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "src/item/abstractitembase.h"

namespace Ui {
class Outliner;
}

class Outliner : public QWidget
{
    Q_OBJECT

public:
    explicit Outliner(QWidget *parent = nullptr);
    ~Outliner();

    void addNode(AbstractItemBase * node);

private:
    Ui::Outliner *ui;
};

#endif // OUTLINER_H
