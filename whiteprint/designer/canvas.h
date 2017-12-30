#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QMap>

#include "wascene.h"
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

	QGraphicsScene * scene();

	//Members
	void addItem(ItemBase *item, qreal x, qreal y, ItemBase *parent = 0);

private:
    WAScene * m_scene;
    QGraphicsView * m_view;

	QMap<QString,Artboard*>*m_artboardList;

	// Helper
    void fakeContent();

signals:

public slots:
};

#endif // CANVAS_H
