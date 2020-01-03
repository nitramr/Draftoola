#include "colorbutton.h"
#include <QPainter>
#include <QDebug>

ColorButton::ColorButton(QWidget *parent) : QToolButton(parent)
{
    setPopupMode(QToolButton::InstantPopup);
}

void ColorButton::setIcon(const QPixmap &pixmap)
{

    QPixmap iconPixmap(pixmap.size());
    iconPixmap.fill(Qt::white);

    QPainter painter(&iconPixmap);
    painter.setPen(Qt::NoPen);

    int x = 0, y = 0, offset = 0, grid = 6;
    QSize count( pixmap.width() / grid, pixmap.height() / grid);

    for(int l = 0;  l <= count.height(); l++)
    {
        for(int r = 0; r <= count.width(); r++)
        {
            if(offset == 0)
            {
                painter.fillRect(QRect( x, y, grid, grid ), Qt::lightGray);
                offset++;
            }
            else offset--;
            x += grid;
        }
        x = 0;
        y += grid;
        offset = (offset == 0) ? 1 : 0;
    }

    painter.drawPixmap(pixmap.rect(), pixmap);

    QIcon icon(iconPixmap);

    QToolButton::setIcon(icon);
}

void ColorButton::setIcon(const QIcon &icon)
{
    QToolButton::setIcon(icon);
}
