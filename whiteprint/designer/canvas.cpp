#include "canvas.h"
#include <QLayout>
#include <QFlags>

#include "whiteprint/item/artboard.h"
#include "whiteprint/item/warect.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsBlurEffect>


Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    m_scene = new WAScene();
	m_scene->setSceneRect(-1000,-1000,4000,4000);

    m_view = new QGraphicsView(m_scene);
	m_view->setBackgroundBrush(QColor(240,240,240));
    m_view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_view->setRenderHint(QPainter::Antialiasing, true);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    m_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	m_artboardList = new QMap<QString, Artboard*>();

    QHBoxLayout * m_layout = new QHBoxLayout();
    m_layout->addWidget(m_view);
    m_layout->setMargin(0);

    this->setLayout(m_layout);

    fakeContent();

}

/***************************************************
 *
 * Members
 *
 ***************************************************/

QGraphicsScene *Canvas::scene()
{
	return m_scene;
}

void Canvas::addItem(ItemBase *item, qreal x, qreal y, ItemBase *parent)
{

	Artboard * m_artboard = dynamic_cast<Artboard*>(item);


	if(m_artboard){ // Item is Artboard

		qDebug() << "Canvas: Item is Artboard";

		m_scene->addItem(m_artboard);
		m_artboardList->insert(m_artboard->name(), m_artboard);

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

/***************************************************
 *
 * Helper
 *
 ***************************************************/

void Canvas::fakeContent()
{

    Artboard *artboard = new Artboard("Artboard1");
    artboard->setPos(this->width()/2,100);
    m_scene->addItem(artboard);
	m_artboardList->insert(artboard->name(), artboard);

	qDebug() << "Init active Panel" << m_scene->activePanel();

//    WARect * rect = new WARect(5,10,30,30);
//    rect->setParentItem(artboard->canvas());




}
