#include "waview.h"
#include <QDebug>

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
	this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));
#endif

	this->setRenderHint(QPainter::Antialiasing, true);
	this->setDragMode(QGraphicsView::RubberBandDrag);
	this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setBackgroundBrush(QColor(240,240,240));

	m_scene = scene;

	m_handleBuffer = 3;
	m_handleFrame = new HandleFrame(m_scene, m_handleBuffer, 1);
	m_handleFrame->setZValue(99999999);
	m_scene->addItem(m_handleFrame);
	m_handleFrame->setup();

}

HandleFrame *WAView::handleFrame() const
{
	return m_handleFrame;
}


void WAView::wheelEvent(QWheelEvent *e)
	{
		if (e->modifiers() & Qt::ControlModifier) {

			qreal scaleX = this->matrix().m11();

			const ViewportAnchor anchor = transformationAnchor();
			this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

			int angle = e->delta();//event->angleDelta().y();
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
			QGraphicsView::wheelEvent(e);
		}
	}

void WAView::keyPressEvent(QKeyEvent *e)
{

	qreal stepperS = 1.0;
	qreal stepperL = 4.0;

	// Single Key + Ctrl
	if (e->modifiers() & Qt::CTRL) {
		switch(e->key())
		{
		case Qt::Key_0 :

			this->resetMatrix();

			break;
		}
	}

	// Single Key + Shift
	if (e->modifiers() & Qt::ShiftModifier) {
		switch(e->key())
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
	switch(e->key())
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

void WAView::keyReleaseEvent(QKeyEvent *e)
{
	switch(e->key())
	{
	case Qt::Key_Space :
		this->setDragMode(QGraphicsView::RubberBandDrag);
		break;

	case Qt::Key_Shift :
		m_handleFrame->setShiftModifier(false);
		break;
	}


	QGraphicsView::keyReleaseEvent(e);
}

