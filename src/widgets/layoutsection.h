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

#ifndef LAYOUTSECTION_H
#define LAYOUTSECTION_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include "flowlayout.h"

class LayoutSectionHeader : public QWidget
{
	Q_OBJECT

//friend class LayoutSection;

public:
    LayoutSectionHeader(QString text, QWidget *menu = nullptr, bool toggle = false, QWidget *parent = nullptr);
    void addButton(QToolButton *button);
    void removeButton(QToolButton *button);
    void setCollapsed(bool isCollapsed);

private:
	void paintEvent(QPaintEvent *);
    QHBoxLayout *m_headerLayout;
	QLabel *m_caption;
    QToolButton *m_btnMenu;
    QToolButton *m_btnCollapse;
    bool m_collapsed;   

signals:
    void sendCollapsedState(bool);

private slots:
    void setCollapsedState();
};


class LayoutSection : public QWidget
{
	Q_OBJECT
public:
    LayoutSection(QString text, QWidget *menu = nullptr, bool toggle = false, QWidget *parent = nullptr);
	void addWidget(QWidget * item);
    void addButton(QToolButton *button);
    void removeButton(QToolButton *button);

private:
    QVBoxLayout *m_flowLayout;
    LayoutSectionHeader * m_header;
    QWidget * m_drawer;

signals:
    void collapsedState(bool);

public slots:
    void setCollapsedState(bool);
};

#endif // LAYOUTSECTION_H
