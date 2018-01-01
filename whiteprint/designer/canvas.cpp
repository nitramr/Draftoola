#include "canvas.h"
#include <QLayout>
#include <QFlags>

#include "whiteprint/item/artboard.h"
#include "whiteprint/item/warect.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsBlurEffect>


Canvas::Canvas(QRectF rect, QWidget *parent) : QWidget(parent)
{
    m_scene = new WAScene();
    m_scene->setSceneRect(rect);

    m_view = new WAView(m_scene);
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

/***************************************************
 *
 * Helper
 *
 ***************************************************/
