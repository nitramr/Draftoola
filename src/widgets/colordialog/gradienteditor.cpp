/**
 * \file gradienteditor.cpp - https://gitlab.com/mattia.basaglia/Qt-Color-Widgets
 *
 * \author Mattia Basaglia
 *
 * \copyright Copyright (C) 2013-2019 Mattia Basaglia
 * \copyright Copyright (C) 2020 Martin Reininger <nitramr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <gradienteditor.h>

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>

#include <utilities.h>

static int cSize = 12;
static int padding = cSize / 2;
static int pWidth = 220;
static int pHeight = cSize + padding;

class GradientEditor::Private
{
public:
    QGradientStops stops;
    Qt::Orientation orientation;
    int highlighted = -1;
    Gradient gradient;
    int selected = -1;
    int drop_index = -1;
    QColor drop_color;
    qreal drop_pos = 0;

    Private()
    {
        gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
        gradient.setSpread(QGradient::RepeatSpread);
    }

    void refresh_gradient()
    {
        gradient.setStops(stops);
    }

    int closest(const QPoint& p, GradientEditor* owner)
    {
        if ( stops.empty() )
            return -1;
        if ( stops.size() == 1 || owner->rangeRect().width()/*owner->geometry().width()*/ <= cSize )
            return 0;
        qreal pos = move_pos(p, owner);

        int i = 1;
        for ( ; i < stops.size()-1; i++ )
            if ( stops[i].first >= pos )
                break;

        if ( stops[i].first - pos < pos - stops[i-1].first )
            return i;
        return i-1;
    }

    qreal move_pos(const QPoint& p, GradientEditor* owner)
    {
        int width;
        qreal x;
        if ( orientation == Qt::Horizontal )
        {
            width = owner->rangeRect().width();//owner->geometry().width();
            x = p.x();
        }
        else
        {
            width = owner->rangeRect().height();//owner->geometry().height();
            x = p.y();
        }
        return (width > cSize) ? qMax(qMin((x - cSize/2) / (width - cSize), 1.0), 0.0) : 0;
    }

    void drop_event(QDropEvent* event, GradientEditor* owner)
    {
        drop_index = closest(event->pos(), owner);
        drop_pos = move_pos(event->pos(), owner);
        if ( drop_index == -1 )
            drop_index = stops.size();

        // Gather up the color
        if ( event->mimeData()->hasColor() )
            drop_color = event->mimeData()->colorData().value<QColor>();
        else if ( event->mimeData()->hasText() )
            drop_color = QColor(event->mimeData()->text());

        owner->update();
    }
    void clear_drop(GradientEditor* owner)
    {
        drop_index = -1;
        drop_color = QColor();
        owner->update();
    }

    void add_stop_data(int& index, qreal& pos, QColor& color)
    {
        if ( stops.empty() )
        {
            index = 0;
            pos = 0;
            color = Qt::black;
            return;
        }
        if ( stops.size() == 1 )
        {
            color = stops[0].second;
            if ( stops[0].first == 1 )
            {
                index = 0;
                pos = 0.5;
            }
            else
            {
                index = 1;
                pos = (stops[0].first + 1) / 2;
            }
            return;
        }

        int i_before = selected;
        if ( i_before == -1 )
            i_before = stops.size() - 1;

        if ( i_before == stops.size() - 1 )
        {
            if ( stops[i_before].first < 1 )
            {
                color = stops[i_before].second;
                pos = (stops[i_before].first + 1) / 2;
                index = stops.size();
                return;
            }
            i_before--;
        }

        index = i_before + 1;
        pos = (stops[i_before].first + stops[i_before+1].first) / 2;
        color = blendColors(stops[i_before].second, stops[i_before+1].second, 0.5);
    }
};

GradientEditor::GradientEditor(QWidget *parent) :
    GradientEditor(Qt::Horizontal, parent)
{}

GradientEditor::GradientEditor(Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent), p(new Private)
{
    p->orientation = orientation;
    setMouseTracking(true);
    resize(sizeHint());
    setAcceptDrops(true);

    if(orientation == Qt::Horizontal){
        setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed) );
    }else setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding) );

}

GradientEditor::~GradientEditor()
{
    delete p;
}

void GradientEditor::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if ( ev->button() == Qt::LeftButton )
    {
        ev->accept();
        qreal pos = p->move_pos(ev->pos(), this);
        auto info = gradientBlendedColorInsert(p->stops, pos);
        p->stops.insert(info.first, info.second);
        p->selected = p->highlighted = info.first;
        p->refresh_gradient();
        emit selectedStopChanged(p->selected);
        update();
    }
    else
    {
        QWidget::mousePressEvent(ev);
    }
}

void GradientEditor::mousePressEvent(QMouseEvent *ev)
{
    if ( ev->button() == Qt::LeftButton )
    {
        ev->accept();
        p->selected = p->highlighted = p->closest(ev->pos(), this);
        emit selectedStopChanged(p->selected);
        update();
    }
    else
    {
        QWidget::mousePressEvent(ev);
    }
}

void GradientEditor::mouseMoveEvent(QMouseEvent *ev)
{
    if ( ev->buttons() & Qt::LeftButton && p->selected != -1 )
    {
        ev->accept();
        qreal pos = p->move_pos(ev->pos(), this);
        if ( p->selected > 0 && pos < p->stops[p->selected-1].first )
        {
            std::swap(p->stops[p->selected], p->stops[p->selected-1]);
            p->selected--;
            emit selectedStopChanged(p->selected);
        }
        else if ( p->selected < p->stops.size()-1 && pos > p->stops[p->selected+1].first )
        {
            std::swap(p->stops[p->selected], p->stops[p->selected+1]);
            p->selected++;
            emit selectedStopChanged(p->selected);
        }
        p->highlighted = p->selected;
        p->stops[p->selected].first = pos;
        p->refresh_gradient();
        update();
    }
    else
    {
        p->highlighted = p->closest(ev->pos(), this);
        update();
    }
}

void GradientEditor::mouseReleaseEvent(QMouseEvent *ev)
{
    if ( ev->button() == Qt::LeftButton && p->selected != -1 )
    {
        ev->accept();
        QRect bound_rect = rect();
        QPoint localpt = ev->localPos().toPoint();
        const int w_margin = 24;
        const int h_margin = 8;
        if ( !bound_rect.contains(localpt) && p->stops.size() > 1 && (
                 localpt.x() < -w_margin || localpt.x() > bound_rect.width() + w_margin ||
                 localpt.y() < -h_margin || localpt.y() > bound_rect.height() + h_margin
                 ) )
        {
            p->stops.remove(p->selected);
            p->highlighted = p->selected = -1;
            p->refresh_gradient();
            emit selectedStopChanged(p->selected);
        }
        emit stopsChanged(p->stops);
        update();
    }
    else
    {
        QWidget::mousePressEvent(ev);
    }
}

void GradientEditor::leaveEvent(QEvent*)
{
    p->highlighted = -1;
    update();
}


QGradientStops GradientEditor::stops() const
{
    return p->stops;
}

void GradientEditor::setStops(const QGradientStops &colors)
{
    p->selected = p->highlighted = -1;
    p->stops = colors;
    p->refresh_gradient();
    emit selectedStopChanged(p->selected);
    emit stopsChanged(p->stops);
    update();
}

Gradient GradientEditor::gradient() const
{
    return p->gradient;
}

void GradientEditor::setGradient(const Gradient &gradient)
{
    setStops(gradient.stops());
}

Qt::Orientation GradientEditor::orientation() const
{
    return p->orientation;
}

void GradientEditor::setOrientation(Qt::Orientation orientation)
{
    p->orientation = orientation;
    update();
}


void GradientEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QLinearGradient linear = p->gradient.linear();

    if(orientation() == Qt::Horizontal)
        linear.setFinalStop(1, 0);
    else
        linear.setFinalStop(0, -1);

    // Draw Background
    QPainterPath path;
    path.addRoundedRect(rangeRect(), rangeRect().height()/2, rangeRect().height()/2);
//    paintGrid(painter, path, QSize(6,3));

    // Draw Gradient
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(palette().color(QPalette::Shadow));
    painter.setBrush(linear);
    painter.drawPath(path);


    // Draw Handles
    int i = 0;
    for ( const QGradientStop& stop : p->stops )
    {
        QPointF position;

        if(orientation() == Qt::Horizontal){
            qreal pos = stop.first * (width() - cSize);
            position = QPointF(pos, height()/2);
        }else {
            qreal pos = stop.first * (height() - cSize);
            position = QPointF(width()/2, pos);
        }


        if ( i == p->selected )
        {
            drawHandle(painter, position, Handle::Selected);
        }
        else if ( i == p->highlighted )
        {
            drawHandle(painter, position, Handle::Highlighted);
        }
        else
        {
            drawHandle(painter, position, Handle::Normal);
        }

        i++;
    }

    if ( p->drop_index != -1 && p->drop_color.isValid() )
    {
        QPointF position;

        if(orientation() == Qt::Horizontal){
             qreal pos = p->drop_pos * (width() - cSize);
            position = QPointF(pos, height()/2);
        }else {
             qreal pos = p->drop_pos * (height() - cSize);
            position = QPointF(width()/2, pos);
        }

        drawHandle(painter, position, Handle::Highlighted);
    }

}

QSize GradientEditor::sizeHint() const
{
    return (orientation() == Qt::Horizontal) ? QSize(pWidth, pHeight) : QSize(pHeight, pWidth);
}

int GradientEditor::selectedStop() const
{
    return p->selected;
}

void GradientEditor::setSelectedStop(int stop)
{
    if ( stop >= -1 && stop < p->stops.size() )
    {
        p->selected = stop;
        emit selectedStopChanged(p->selected);
    }
}

QColor GradientEditor::selectedColor() const
{
    if ( p->selected != -1 )
        return p->stops[p->selected].second;
    return {};
}

void GradientEditor::setSelectedColor(const QColor& color)
{
    if ( p->selected != -1 )
    {
        p->stops[p->selected].second = color;
        p->refresh_gradient();
        update();
    }
}


void GradientEditor::dragEnterEvent(QDragEnterEvent *event)
{
    p->drop_event(event, this);

    if ( p->drop_color.isValid() && p->drop_index != -1 )
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void GradientEditor::dragMoveEvent(QDragMoveEvent* event)
{
    p->drop_event(event, this);
}

void GradientEditor::dragLeaveEvent(QDragLeaveEvent *)
{
    p->clear_drop(this);
}

void GradientEditor::dropEvent(QDropEvent *event)
{
    p->drop_event(event, this);

    if ( !p->drop_color.isValid() || p->drop_index == -1 )
        return;

    p->stops.insert(p->drop_index, {p->drop_pos, p->drop_color});
    p->refresh_gradient();
    p->selected = p->drop_index;
    event->accept();
    p->clear_drop(this);
    emit selectedStopChanged(p->selected);
}

void GradientEditor::drawHandle(QPainter &painter, QPointF point, Handle state)
{
    QPoint offset;

    if(orientation() == Qt::Horizontal){
        offset = QPoint(0, cSize/2);
    }else offset = QPoint(cSize/2, 0);

    QRectF cursor(point - offset, QSize(cSize, cSize));

    QPen pen;
    switch(state){
    case Handle::Selected:
        pen = QPen(QColor(0, 128, 255));
        break;
    case Handle::Highlighted:
        pen = QPen(Qt::black);
        break;
    case Handle::Normal:
        pen = QPen(Qt::darkGray);
        break;
    }

    pen.setWidth(4);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(cursor.adjusted(2,2,-2,-2));

    pen.setColor(Qt::white);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(cursor.adjusted(2,2,-2,-2));
}

QRect GradientEditor::rangeRect() const
{
    if(orientation() == Qt::Horizontal){
        return contentsRect().adjusted(0,padding, 0, -padding);
    }else return contentsRect().adjusted(padding,0, -padding, 0);

}

void GradientEditor::addStop()
{
    int index = -1;
    qreal pos = 0;
    QColor color;
    p->add_stop_data(index, pos, color);
    p->stops.insert(index, {pos, color});
    p->selected = p->highlighted = index;
    p->refresh_gradient();
    update();
    emit selectedStopChanged(p->selected);
}

void GradientEditor::removeStop()
{
    if ( p->stops.size() < 2 )
        return;

    int selected = p->selected;
    if ( selected == -1 )
        selected = p->stops.size() - 1;
    p->stops.remove(selected);
    p->refresh_gradient();

    if ( p->selected != -1 )
    {
        p->selected = -1;
        emit selectedStopChanged(p->selected);
    }

    update();

}

