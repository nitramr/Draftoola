#include "canvas.h"
#include <QLayout>
#include <QFlags>

#include "whiteprint/item/artboard.h"
#include "whiteprint/item/warect.h"
#include "whiteprint/item/watext.h"

Canvas::Canvas(QRectF rect, QWidget *parent) : QWidget(parent)
{
    m_scene = new WAScene();
	m_scene->setSceneRect(rect);

    m_view = new WAView(m_scene);

	m_artboardList = new QMap<QString, Artboard*>();

    QHBoxLayout * m_layout = new QHBoxLayout();
    m_layout->addWidget(m_view);
    m_layout->setMargin(0);

    this->setLayout(m_layout);



}


/***************************************************
 *
 * Members
 *
 ***************************************************/

//QGraphicsScene *Canvas::scene()
//{
//	return m_scene;
//}

WAView *Canvas::view() const
{
	return m_view;
}


void Canvas::addItem(QGraphicsItem *item, qreal x, qreal y, QGraphicsItem *parent)
{

	Artboard * m_artboard = dynamic_cast<Artboard*>(item);


	if(m_artboard){ // Item is Artboard

		qDebug() << "Canvas: Item is Artboard";

		m_scene->addItem(m_artboard);
		m_artboardList->insert(m_artboard->name(), m_artboard);
        m_artboard->setPos(x,y);

	}else{ // Item is no Artboard

		qDebug() << "Canvas: Item is no Artboard";

		if(parent == 0 && m_artboardList->count() > 0){

			qDebug() << "Canvas: Item has no Parent";
			Artboard * artboard = m_artboardList->first();

			if(artboard){
				item->setParentItem(artboard->canvas());
				item->setPos(x,y);
				qDebug() << "Canvas: add Item to Artboard";
			}

		}else if(parent){

			qDebug() << "Canvas: Item has Parent";

			item->setParentItem(parent);
			item->setPos(x,y);
			qDebug() << "Canvas: add Item to Parent";
		}

	}


}

void Canvas::addItem(QGraphicsTextItem *item, qreal x, qreal y, QGraphicsItem *parent)
{
	qDebug() << "Canvas: Item is no Artboard";

	if(parent == 0 && m_artboardList->count() > 0){

		qDebug() << "Canvas: Item has no Parent";
		Artboard * artboard = m_artboardList->first();

		if(artboard){
			item->setParentItem(artboard->canvas());
			item->setPos(x,y);
			qDebug() << "Canvas: add Item to Artboard";
		}

	}else if(parent){

		qDebug() << "Canvas: Item has Parent";

		item->setParentItem(parent);
		item->setPos(x,y);
		qDebug() << "Canvas: add Item to Parent";
	}
}

/***************************************************
 *
 * Helper
 *
 ***************************************************/
