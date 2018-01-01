#include "wascene.h"
#include <QDebug>
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

WAScene::WAScene(QObject *parent) : QGraphicsScene(parent)
{
    m_scaleFactor = 1.0;
    m_handleBuffer = 3;
    m_handleFrame = new HandleFrame(m_handleBuffer);
    m_handleFrame->setZValue(99999999);
    this->addItem(m_handleFrame);

    m_handleFrame->installFilter();

    connect(this, SIGNAL(selectionChanged()), this,SLOT(updateHandleFrame()));
    connect(m_handleFrame, SIGNAL(emitItemChange()), this, SLOT(updateItemProperties()));
}

void WAScene::setScaleFactor(qreal factor)
{
    m_scaleFactor = factor;
    m_handleFrame->setScaleFactor(m_scaleFactor);
}

qreal WAScene::scaleFactor() const
{
    return m_scaleFactor;
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void WAScene::updateHandleFrame()
{

    QList<QGraphicsItem*> selecitems = this->selectedItems();

    if(selectedItems().size() == 0){
        m_handleFrame->setVisible(false);
        m_handleFrame->setHost(new ItemBase());
        emit emitActiveItem(0);
        return;
    }else if(selectedItems().size()==1){
        ItemBase* m_itemBase = dynamic_cast<ItemBase*>(selecitems[0]);
        ArtboardLabel* m_artboardLabel = dynamic_cast<ArtboardLabel*>(selecitems[0]);
        if(m_itemBase){

            qreal posX = m_itemBase->scenePos().x();
            qreal posY = m_itemBase->scenePos().y();

            m_handleFrame->setVisible(true);
            m_handleFrame->setRect(m_itemBase->rect());
            m_handleFrame->setPos(posX , posY);
            m_handleFrame->setHost(m_itemBase);
            m_handleFrame->setCornerPositions();

            emit emitActiveItem(m_itemBase);

        } else if(m_artboardLabel){

            Artboard * m_artboard = dynamic_cast<Artboard*>(m_artboardLabel->parentItem());
            if(!m_artboard) return;

            qreal posX = m_artboard->scenePos().x();
            qreal posY = m_artboard->scenePos().y();

            m_handleFrame->setVisible(true);
            m_handleFrame->setRect(m_artboard->rect());
            m_handleFrame->setPos(posX , posY );
            m_handleFrame->setHost(m_artboard);
            m_handleFrame->setCornerPositions();


            emit emitActiveItem(m_artboard);

        }else {
            m_handleFrame->setVisible(false);
            m_handleFrame->setHost(new ItemBase());
            emit emitActiveItem(0);
            return;
        }
    }

}

void WAScene::updateItemProperties()
{
    QList<QGraphicsItem*> selecitems = this->selectedItems();

    if(selectedItems().size()==1){
        ItemBase* m_itemBase = dynamic_cast<ItemBase*>(selecitems[0]);
        if(m_itemBase){
            emit emitActiveItem(m_itemBase);
        }

    }
}


/***************************************************
 *
 * Events
 *
 ***************************************************/


void WAScene::keyPressEvent(QKeyEvent *e)
{
    qreal stepperS = 1.0;
    qreal stepperL = 4.0;

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
    }

    //QGraphicsScene::keyPressEvent(e);
}

void WAScene::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Shift :
        m_handleFrame->setShiftModifier(false);
        break;
    }

    QGraphicsScene::keyReleaseEvent(e);
}



