/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

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

#include "propertyexportlevel.h"
#include "ui_propertyexportlevel.h"

#include <QPainter>
#include <QDebug>
#include <QMap>
#include <utilities.h>

PropertyExportLevel::PropertyExportLevel(QWidget *parent) : PropertyExportLevel(ExportLevel(), parent) {}

PropertyExportLevel::PropertyExportLevel(ExportLevel exportLevel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::propertyExportLevel)
{
    ui->setupUi(this);    

    QMap<QString, ExportLevel::FileFormat> * fileFormatList = new QMap<QString, ExportLevel::FileFormat>();
    fileFormatList->insert("PNG", ExportLevel::FileFormat::PNG);
    fileFormatList->insert("JPG", ExportLevel::FileFormat::JPG);
    fileFormatList->insert("SVG", ExportLevel::FileFormat::SVG);
    fileFormatList->insert("PDF", ExportLevel::FileFormat::PDF);

    ui->comboFormat->addItems(QStringList(fileFormatList->keys()));

    ui->comboSize->addItem("1x");
    ui->comboSize->addItem("2x");
    ui->comboSize->addItem("3x");
    ui->comboSize->setCurrentText("1x");

    setExportLevel(exportLevel);
}

PropertyExportLevel::~PropertyExportLevel()
{
    delete ui;
}

void PropertyExportLevel::setExportLevel(ExportLevel exportLevel)
{
    disconnectSlots();

    m_exportLevel = exportLevel;

    switch(exportLevel.fileFormat()){
        case ExportLevel::FileFormat::PNG:
            ui->comboFormat->setCurrentText("PNG");
        break;
    case ExportLevel::FileFormat::JPG:
            ui->comboFormat->setCurrentText("JPG");
        break;
    case ExportLevel::FileFormat::SVG:
            ui->comboFormat->setCurrentText("SVG");
        break;
    case ExportLevel::FileFormat::PDF:
            ui->comboFormat->setCurrentText("PDF");
        break;
    default:
        break;
    }

    ui->comboSize->setCurrentText(QString::number(exportLevel.renderLevel()) + "x");
    ui->comboPath->setCurrentText(exportLevel.path());

    connectSlots();
}

ExportLevel PropertyExportLevel::exportLevel() const
{
    return m_exportLevel;
}

void PropertyExportLevel::removeClick()
{
    emit remove(this);
}

void PropertyExportLevel::connectSlots()
{
    connect(ui->btnDelete, &QToolButton::clicked, this, &PropertyExportLevel::removeClick);
    connect(ui->comboSize, &QComboBox::currentTextChanged, this, &PropertyExportLevel::updateFill);
    connect(ui->comboPath, &QComboBox::currentTextChanged, this, &PropertyExportLevel::updateFill);
    connect(ui->comboFormat, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyExportLevel::updateFill);
}

void PropertyExportLevel::disconnectSlots()
{
    disconnect(ui->btnDelete, &QToolButton::clicked, this, &PropertyExportLevel::removeClick);
    disconnect(ui->comboSize, &QComboBox::currentTextChanged, this, &PropertyExportLevel::updateFill);
    disconnect(ui->comboPath, &QComboBox::currentTextChanged, this, &PropertyExportLevel::updateFill);
    disconnect(ui->comboFormat, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PropertyExportLevel::updateFill);
}

void PropertyExportLevel::updateFill()
{
    QString path = ui->comboPath->currentText();



    ExportLevel::FileFormat fileFormat = ExportLevel::FileFormat::PNG;
    QString fileString = ui->comboFormat->currentText();
    if(fileString == "PNG"){
        fileFormat = ExportLevel::FileFormat::PNG;
    }else if(fileString == "JPG"){
        fileFormat = ExportLevel::FileFormat::JPG;
    }else if(fileString == "PDF"){
        fileFormat = ExportLevel::FileFormat::PDF;
    }if(fileString == "SVG"){
        fileFormat = ExportLevel::FileFormat::SVG;
    }


    double renderLevel = 1;

    // TODO: Pattern need to optimize for suffix (x=multiplier; w=fixed width)
    QRegularExpression re("(\\d+.\\d)|(\\d+)");
    QRegularExpressionMatch match = re.match(ui->comboSize->currentText());
    if (match.hasMatch()) {
        QString matched = match.captured(0);
        renderLevel = matched.toDouble();
    }

    m_exportLevel.setRenderLevel(renderLevel);
    m_exportLevel.setPath(path);
    m_exportLevel.setFileFormat(fileFormat);

    emit hasChanged(true);
}
