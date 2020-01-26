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

#include "popupmenu.h"
#include <QEvent>
#include <QBoxLayout>

/*!
 * \brief [CTR]
 * \param widget
 */
PopupMenu::PopupMenu(QWidget *contentWidget)
{
    if(contentWidget == nullptr) contentWidget = new QWidget();

	QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(contentWidget);
	layout->setMargin(1);

	QWidget *panel = new QWidget();
    panel->setMinimumSize(contentWidget->size());
	panel->setLayout(layout);

	QWidgetAction * action = new QWidgetAction(this);
	action->setDefaultWidget(panel);

    contentWidget->installEventFilter(this);

	this->addAction(action);

}

bool PopupMenu::eventFilter(QObject *obj, QEvent *event)
{

	// prevent that menu is close by interact with the background
	if (event->type() == QEvent::MouseButtonPress ||
			event->type() == QEvent::MouseButtonDblClick ||
			event->type() == QEvent::MouseMove) {

		return true;
	}

		return QObject::eventFilter(obj, event);

}
