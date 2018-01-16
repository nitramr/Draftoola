#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QWidget>

#include "whiteprint/item/artboard.h"
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/warect.h"
#include "whiteprint/item/waoval.h"
#include "whiteprint/item/watext.h"


namespace Ui {
class ItemProperties;
}

class ItemProperties : public QWidget
{
    Q_OBJECT

public:
    explicit ItemProperties(QWidget *parent = 0);
    ~ItemProperties();

	void setActiveItem(QGraphicsItem *item);

private:
    Ui::ItemProperties *ui;

    Artboard * m_artboard;
	WARect * m_itemRect;
	WAOval * m_itemOval;
	WAText * m_itemText;

    void loadProperties();
    void resetItems();
};

#endif // ITEMPROPERTIES_H
