#include "waview.h"
#include <QDebug>

#include "wascene.h"

WAView::WAView(QWidget * parent) : WAView(0, parent){}
WAView::WAView(QGraphicsScene * scene, QWidget * parent) : QGraphicsView(scene, parent)
{

}


void WAView::wheelEvent(QWheelEvent *event)
    {
        if (event->modifiers() & Qt::ControlModifier) {

            qreal scaleX = this->matrix().m11();

            const ViewportAnchor anchor = transformationAnchor();
            setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

            int angle = event->delta();//event->angleDelta().y();
            qreal factor;
            if(angle == 0){
                factor = 1.0;
            }
            else if (angle > 0) {
                if(scaleX >= 3) return; // limit zoom level to 300%
                factor = 1.05;
            }else {
                if(scaleX <= 0.1) return; // limit zoom level to 10%
                factor = 0.95;
            }


            qDebug() << "Steps:" << angle << "ScaleX:" << scaleX;

            scale(factor, factor);
            setTransformationAnchor(anchor);

            WAScene * waScene = dynamic_cast<WAScene*>(this->scene());
            if(waScene){
                waScene->setScaleFactor(this->matrix().m11());
            }

        } else {
            QGraphicsView::wheelEvent(event);
        }
    }
