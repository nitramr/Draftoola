#include "waview.h"
#include <QDebug>
#include <QTransform>

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif

#include "wascene.h"
#include "handleframe.h"

WAView::WAView(WAScene * scene, QWidget * parent) : QGraphicsView(scene, parent)
{
#ifndef QT_NO_OPENGL
	//this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));
#endif

//	this->setRenderHint(QPainter::Antialiasing, true);
//	this->setRenderHints( QPainter::SmoothPixmapTransform );
	this->setDragMode(QGraphicsView::RubberBandDrag);
	this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setBackgroundBrush(QColor(240,240,240));
//	this->setRubberBandSelectionMode(Qt::ContainsItemShape);


	m_scene = scene;
	m_handleBuffer = 3;
	m_grid = 1;

	m_handleFrame = new HandleFrame(m_scene, m_handleBuffer, m_grid);
	m_scene->addItem(m_handleFrame);
	m_handleFrame->setup();

	counter = 0;
	group = new WAGroup();

}

HandleFrame *WAView::handleFrame() const
{
	return m_handleFrame;
}


void WAView::wheelEvent(QWheelEvent *event)
	{
		if (event->modifiers() & Qt::ControlModifier) {

			qreal scaleX = this->matrix().m11();

			const ViewportAnchor anchor = transformationAnchor();
			this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

			int angle = event->delta();//event->angleDelta().y();
			qreal factor = 1;
			if(angle == 0){
				factor = 1.0;
			}
			else if (angle < 0) {
				if(scaleX >= 25) return; // limit zoom level to 2500%
				factor += .05;
			}else {
				if(scaleX <= 0.1) return; // limit zoom level to 10%
				factor -= .05;
			}

			this->scale(factor, factor);
			this->setTransformationAnchor(anchor);

			m_handleFrame->setScaleFactor(this->matrix().m11());

		} else {
			QGraphicsView::wheelEvent(event);
		}
	}

void WAView::keyPressEvent(QKeyEvent *event)
{

	qreal stepperS = 1.0;
	qreal stepperL = 4.0;

	// Single Key + Ctrl
	if (event->modifiers() & Qt::CTRL) {
		switch(event->key())
		{
		case Qt::Key_0 :

			this->resetMatrix();

			break;
		}
	}

	// Single Key + Shift
	if (event->modifiers() & Qt::ShiftModifier) {
		switch(event->key())
		{
		case Qt::Key_Left :
			m_handleFrame->moveBy(-stepperL, 0);

			break;
		case Qt::Key_Right :
			m_handleFrame->moveBy(stepperL, 0);

			break;
		case Qt::Key_Up :
			m_handleFrame->moveBy(0, -stepperL);

			break;
		case Qt::Key_Down :
			m_handleFrame->moveBy(0, stepperL);

			break;
		}
	}

	// Single Key
	switch(event->key())
	{
	case Qt::Key_Left :
		m_handleFrame->moveBy(-stepperS, 0);

		break;
	case Qt::Key_Right :
		m_handleFrame->moveBy(stepperS, 0);

		break;
	case Qt::Key_Up :
		m_handleFrame->moveBy(0, -stepperS);

		break;
	case Qt::Key_Down :
		m_handleFrame->moveBy(0, stepperS);

		break;
	case Qt::Key_Shift :
		m_handleFrame->setShiftModifier(true);
		break;

	case Qt::Key_Space:
		this->setDragMode(QGraphicsView::ScrollHandDrag);

		break;

	}


//	QGraphicsView::keyPressEvent(e);
}

void WAView::keyReleaseEvent(QKeyEvent *event)
{
	switch(event->key())
	{
	case Qt::Key_Space :
		this->setDragMode(QGraphicsView::RubberBandDrag);
		break;

	case Qt::Key_Shift :
		m_handleFrame->setShiftModifier(false);
		break;

	case Qt::Key_V:{

		m_scene->clearSelection();
		qreal exFactor = 4;
		QRectF targetRect = QRectF(0,0,375*exFactor,667*exFactor);
		QImage image(QSize(targetRect.width(), targetRect.height()), QImage::Format_ARGB32_Premultiplied);
		image.fill(Qt::transparent);

		QPainter painter(&image);
		//painter.setRenderHint(QPainter::HighQualityAntialiasing);
		m_scene->render(&painter, targetRect, QRectF(0,0,375,667));
		image.save("file_name.png");


//		QList<QGraphicsItem *> selectedItems = m_scene->items();
//		foreach(QGraphicsItem *current, selectedItems) {

//			QGraphicsItemGroup * itemArtboard = dynamic_cast<QGraphicsItemGroup*>(current);

//			qDebug() << "ItemGroup" << itemArtboard;
//		}

//		if(counter == 0){
//			WARect * rectG = new WARect(50,50);
//			rectG->setFills(Fills("rect", QColor(Qt::blue)));
//			rectG->setPos(0,0);
//			rectG->setRotation(30);
//			m_scene->addItem(rectG);

//			Stroke stroke("TestEllipseStroke", QBrush(QColor(128,208,23)),1);

//			WAOval * ovalG = new WAOval(50,50);
//			ovalG->setFills(Fills("oval", QColor(Qt::green)));
//			ovalG->setStroke(stroke);
//			ovalG->setStrokePosition(StrokePosition::Inner);
//			rectG->setPos(70,10);
//			m_scene->addItem(ovalG);


//			group->addToGroup(rectG);
//			group->addToGroup(ovalG);
//			group->setPos(10,10);
//			m_scene->addItem(group);

//			qDebug() << "Count1";
//		}
//		if(counter == 1){
//			group->setRotation(45);

//			qDebug() << "Count2";
//		}
//		if(counter == 2){
//			m_scene->destroyItemGroup(group);
//			qDebug() << "Count3";
//		}

//		if(counter == 3){
//			WARect * rectG = new WARect(50,50);
//			rectG->setFills(Fills("rect", QColor(Qt::blue)));
//			rectG->setPos(0,0);
//			rectG->setRotation(30);
//			m_scene->addItem(rectG);

//			Stroke stroke("TestEllipseStroke", QBrush(QColor(128,208,23)),1);

//			WAOval * ovalG = new WAOval(50,50);
//			ovalG->setFills(Fills("oval", QColor(Qt::green)));
//			ovalG->setStroke(stroke);
//			ovalG->setStrokePosition(StrokePosition::Inner);
//			rectG->setPos(70,10);
//			m_scene->addItem(ovalG);

//			group = new WAGroup();
//			group->addToGroup(rectG);
//			group->addToGroup(ovalG);
//			group->setPos(50,50);
//			m_scene->addItem(group);

//			qDebug() << "Count4";
//		}

//		if(counter == 4){

//			QTransform transform = group->transform();
//			transform.scale(2, 1);

//			group->setTransform(transform);
//			qDebug() << "Count5";

//		}

//		counter++;
		break;
	}
	}


	QGraphicsView::keyReleaseEvent(event);
}

void WAView::mouseMoveEvent(QMouseEvent *event)
{
	QGraphicsView::mouseMoveEvent(event);

}

void WAView::mousePressEvent(QMouseEvent *event)
{
	QGraphicsView::mousePressEvent(event);

//	if(!m_handleFrame->isHovered()){
//		m_handleFrame->unGroup();
//	}
}

void WAView::mouseReleaseEvent(QMouseEvent *event)
{
	QGraphicsView::mouseReleaseEvent(event);
	//m_handleFrame->group();

}

