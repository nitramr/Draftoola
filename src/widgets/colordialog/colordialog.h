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

#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QWidget>

#include <utilities.h>
#include <fills.h>
#include <stroke.h>
#include <shadow.h>
#include <QTabBar>

namespace Ui {
class ColorDialog;
}

class ColorDialog : public QWidget
{
    Q_OBJECT

    enum Mode {
        FillLayout = 0,
        StrokeLayout = 1,
        ShadowLayout = 2
    };


public:
    explicit ColorDialog(QWidget *parent = nullptr);
    ~ColorDialog();

    void setProperty(AbstractItemProperty *property);

    Gradient gradient() const;
    Color color() const;
    QString imagePath() const;
    qreal opacity() const;
    FillType fillType() const;
    Fills::FillMode fillMode() const;

    Mode mode() const;

private:
    Ui::ColorDialog *ui;

    Mode            m_mode;
    FillType        m_fillType;
    Fills::FillMode m_fillMode;
    Color           m_color;
    Gradient        m_gradient;
    QString         m_imagePath;
    qreal           m_opacity;
    QTabBar        *m_tabBar;

    void configurateDialog();
    void selectTab();


signals:

    void propertyChanged();

public slots:
    void updateProperty();

private slots:
    void changeTabs(int index);

};

#endif // COLORDIALOG_H
