#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QMenu>
#include <QWidgetAction>

class PopupMenu : public QMenu
{
public:
    PopupMenu(QWidget*widget);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
};

#endif // POPUPMENU_H
