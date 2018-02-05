#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsDropShadowEffect>
#include <QMap>

#include "wascene.h"
#include "waview.h"
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QRectF rect = QRectF(-2000, -2000, 4000,4000), QWidget *parent = 0);

//	QGraphicsScene * scene();
	WAView * view() const;

	//Members
	void addItem(ItemBase *item, qreal x = 0, qreal y = 0, QGraphicsItem *parent = 0);
	void addItem(QGraphicsTextItem* item, qreal x = 0, qreal y = 0, QGraphicsItem *parent = 0);

private:
    WAScene * m_scene;
    WAView * m_view;

	QMap<QString,Artboard*>*m_artboardList;


signals:

public slots:
};

#endif // CANVAS_H
