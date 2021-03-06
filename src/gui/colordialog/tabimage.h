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

#ifndef TABIMAGE_H
#define TABIMAGE_H

#include <QComboBox>
#include <QLabel>
#include <QWidget>
#include <fills.h>

namespace Ui {
class TabImage;
}

class TabImage : public QWidget
{
    Q_OBJECT

public:
    explicit TabImage(QWidget *parent = nullptr);
    ~TabImage();

    QString imagePath() const;
    void setImagePath(const QString path);

    Fills::FillMode fillMode() const;
    void setFillMode(Fills::FillMode fillMode);

private:
    Ui::TabImage *ui;

    QString m_imagePath;
    Fills::FillMode m_fillMode;
    QComboBox *m_comboFillMode;
    QLabel *m_labelFillMode;
    QLabel *m_preview;

    void connectSlots();
    void disconnectSlots();

    bool loadFile(const QString &fileName);

public slots:

    void updateProperty();

private slots:
    void open();


signals:
    void imageChanged();

};

#endif // TABIMAGE_H
