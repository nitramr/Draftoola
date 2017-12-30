#include "wascene.h"
#include <QDebug>
#include "whiteprint/item/itembase.h"
#include "whiteprint/item/artboard.h"

WAScene::WAScene(QObject *parent) : QGraphicsScene(parent)
{
   m_handleBuffer = 5;
   m_handleFrame = new HandleFrame(m_handleBuffer);
   m_handleFrame->setZValue(99999999);
   this->addItem(m_handleFrame);

   m_handleFrame->installFilter();

   connect(this, SIGNAL(selectionChanged()), this,SLOT(updateHandleFrame()));
}

void WAScene::updateHandleFrame()
{

    QList<QGraphicsItem*> selecitems = this->selectedItems();

    if(selectedItems().size() == 0){
        m_handleFrame->setVisible(false);
        m_handleFrame->setHost(new ItemBase());
        return;
    }else if(selectedItems().size()==1){
            ItemBase* m_itemBase = dynamic_cast<ItemBase*>(selecitems[0]);
            ArtboardLabel* m_artboardLabel = dynamic_cast<ArtboardLabel*>(selecitems[0]);
            if(m_itemBase){

                QRectF frameRect = m_itemBase->rect();

                QRectF rect(frameRect.x(), frameRect.y(), frameRect.width() + 2 * m_handleBuffer, frameRect.height() + 2 * m_handleBuffer);
                qreal posX = m_itemBase->scenePos().x();
                qreal posY = m_itemBase->scenePos().y();

                m_handleFrame->setVisible(true);
               // m_handleFrame->setIsResize(false);
                m_handleFrame->setPos(posX - m_handleBuffer, posY - m_handleBuffer);
                m_handleFrame->setRect(rect);
                m_handleFrame->setHost(m_itemBase);
                m_handleFrame->setCornerPositions();

            } else if(m_artboardLabel){

                Artboard * artboard = dynamic_cast<Artboard*>(m_artboardLabel->parentItem());
                if(!artboard) return;

                QRectF frameRect = artboard->rect();

                QRectF rect(frameRect.x(), frameRect.y(), frameRect.width() + 2 * m_handleBuffer, frameRect.height() + 2 * m_handleBuffer);
                qreal posX = artboard->scenePos().x();
                qreal posY = artboard->scenePos().y();

                m_handleFrame->setVisible(true);
              //  m_handleFrame->setIsResize(true);
                m_handleFrame->setPos(posX - m_handleBuffer, posY - m_handleBuffer);
                m_handleFrame->setRect(rect);
                m_handleFrame->setHost(artboard);
                m_handleFrame->setCornerPositions();

            }else {
                m_handleFrame->setVisible(false);
                m_handleFrame->setHost(new ItemBase());
                return;
            }
        }



}

