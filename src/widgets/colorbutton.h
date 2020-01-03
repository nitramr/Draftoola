#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QToolButton>

class ColorButton : public QToolButton
{
public:
    ColorButton(QWidget *parent);

    void setIcon(const QPixmap &pixmap);
    void setIcon(const QIcon &icon);

private:
};

#endif // COLORBUTTON_H
