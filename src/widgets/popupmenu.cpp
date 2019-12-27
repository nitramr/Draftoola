#include "popupmenu.h"
#include <QEvent>
#include <QBoxLayout>

PopupMenu::PopupMenu(QWidget *widget)
{
    if(widget == nullptr) widget = new QWidget();

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(widget);
	layout->setMargin(1);

	QWidget *panel = new QWidget();
	panel->setMinimumSize(widget->size());
	panel->setLayout(layout);

	QWidgetAction * action = new QWidgetAction(this);
	action->setDefaultWidget(panel);

	widget->installEventFilter(this);

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
