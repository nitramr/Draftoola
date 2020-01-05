#include "tool_outliner.h"
#include "ui_tool_outliner.h"
#include "src/item/artboard.h"
#include "src/designer/canvasview.h"

#include <QDebug>

Outliner::Outliner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outliner)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Artboards");
}

Outliner::~Outliner()
{
    delete ui;
}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void Outliner::updateList()
{
    CanvasView *canvas = static_cast<CanvasView*>(sender());

    if(canvas){

        ui->treeWidget->clear();

        foreach(Artboard* artboard, canvas->artboardList()){
            QTreeWidgetItem * twi = new QTreeWidgetItem();
            twi->setText(0, artboard->name());

            foreach(AbstractItemBase *item, artboard->childItems()){
                QTreeWidgetItem * twc = new QTreeWidgetItem();
                twc->setText(0, item->name());
                twi->addChild(twc);

            }
            ui->treeWidget->addTopLevelItem(twi);
        }

    }

}
