/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "tabimage.h"
#include "ui_tabimage.h"

#include <QColorSpace>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QStandardPaths>

TabImage::TabImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabImage)
{
    ui->setupUi(this);

    QToolButton *btn_open = new QToolButton;
    btn_open->setIcon( QIcon(":/icons/dark/folder-open.svg") );

    m_comboFillMode = new QComboBox();
    m_comboFillMode->addItem(tr("Fit"), QVariant(Fills::FillMode::Fit));
    m_comboFillMode->addItem(tr("Fill"), QVariant(Fills::FillMode::Fill));
    m_comboFillMode->addItem(tr("Tile"), QVariant(Fills::FillMode::Tile));
    m_comboFillMode->addItem(tr("Stretch"), QVariant(Fills::FillMode::Stretch));


    m_labelFillMode = new QLabel(tr("Fill Mode"));


    m_preview = new QLabel();
    m_preview->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_preview->setBackgroundRole(QPalette::Base);
    m_preview->setFixedHeight(100);
    m_preview->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);


    ui->secImage->setText(tr("Image"));
    ui->secImage->addHeaderWidget(btn_open);
    ui->secImage->addWidget(m_preview);
    ui->secImage->addWidget(m_labelFillMode);
    ui->secImage->addWidget(m_comboFillMode);


    this->connect(btn_open, &QToolButton::clicked, this, &TabImage::open);

}

TabImage::~TabImage()
{
    delete ui;
}


Fills::FillMode TabImage::fillMode() const
{
    return m_fillMode;
}

QString TabImage::imagePath() const
{
    return m_imagePath;
}

void TabImage::setImagePath(const QString path)
{
    m_imagePath = path;
    QPixmap pix;

    if(pix.load(m_imagePath)){

        int limit = qMin(m_preview->width(), m_preview->height());

        QSize size(limit,limit);
        pix = pix.scaled(size,Qt::KeepAspectRatio, Qt::TransformationMode::FastTransformation);

        m_preview->setPixmap(pix);
    }
}

void TabImage::setFillMode(Fills::FillMode fillMode)
{
    disconnectSlots();
    m_fillMode = fillMode;

    int indexMode = 0;
    for(int i = 0; i < m_comboFillMode->count(); i++){
        if(fillMode == static_cast<Fills::FillMode>(m_comboFillMode->itemData(i).toInt())){
            indexMode = i;
            break;
        }
    }
    m_comboFillMode->setCurrentIndex(indexMode);

    connectSlots();
}


void TabImage::connectSlots()
{
    connect(m_comboFillMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TabImage::updateProperty);
}

void TabImage::disconnectSlots()
{
    disconnect(m_comboFillMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TabImage::updateProperty);
}

void TabImage::updateProperty()
{
    m_fillMode = static_cast<Fills::FillMode>(m_comboFillMode->currentData().toInt()) ;


    emit imageChanged();
}

static void initializeImageFileDialog(QFileDialog &dialog)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    dialog.setNameFilter("All Images (*.png *.bmp *.jpg);;JPG Files (*.jpg *.jpeg);;BMP Files (*.bmp);;PNG Files (*.png)");
}

void TabImage::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool TabImage::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImagePath(fileName);
    updateProperty();

    return true;
}
