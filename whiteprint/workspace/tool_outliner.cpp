#include "tool_outliner.h"
#include "ui_outliner.h"

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

void Outliner::addNode(ItemBase *node)
{
    QTreeWidgetItem * twi = new QTreeWidgetItem();
    twi->setText(0, node->name());

    qDebug() << node->name();

    ui->treeWidget->addTopLevelItem(twi);

}
