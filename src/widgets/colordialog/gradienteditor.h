/**
 * \file gradienteditor.h - https://gitlab.com/mattia.basaglia/Qt-Color-Widgets
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


#ifndef GRADIENT_EDITOR_H
#define GRADIENT_EDITOR_H

#include <QWidget>
#include <QGradient>

#include <gradient.h>


/**
 * \brief A slider that moves on top of a gradient
 */
class GradientEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QGradientStops stops READ stops WRITE setStops NOTIFY stopsChanged)
    Q_PROPERTY(Gradient gradient READ gradient WRITE setGradient)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(int selectedStop READ selectedStop WRITE setSelectedStop NOTIFY selectedStopChanged)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)

public:
    explicit GradientEditor(QWidget *parent = 0);
    explicit GradientEditor(Qt::Orientation orientation, QWidget *parent = 0);
    ~GradientEditor();

    QSize sizeHint() const override;

    /// Get the colors that make up the gradient
    QGradientStops stops() const;
    /// Set the colors that make up the gradient
    void setStops(const QGradientStops &colors);

    /// Get the gradient
    Gradient gradient() const;
    /// Set the gradient
    void setGradient(const Gradient &gradient);

    Qt::Orientation orientation() const;

    /**
     * \brief Index of the currently selected gradient stop (or -1 if there is no selection)
     */
    int selectedStop() const;

    /**
     * \brief Color of the selected stop
     */
    QColor selectedColor() const;

public Q_SLOTS:
    void setOrientation(Qt::Orientation);
    void setSelectedStop(int stop);
    void setSelectedColor(const QColor& color);
    void addStop();
    void removeStop();

Q_SIGNALS:
    void stopsChanged(const QGradientStops&);
    void selectedStopChanged(int);

protected:
    void paintEvent(QPaintEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void leaveEvent(QEvent * event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent* event) override;

private:
    class Private;
    Private * const p;

    enum Handle{
        Selected = 0,
        Highlighted = 1,
        Normal = 2
    };

    void drawHandle(QPainter &painter, QPointF point, Handle state);
    QRect rangeRect() const;
};


inline QColor blendColors(const QColor& a, const QColor& b, qreal ratio)
{
    return QColor::fromRgbF(
        a.redF()   * (1-ratio) + b.redF()   * ratio,
        a.greenF() * (1-ratio) + b.greenF() * ratio,
        a.blueF()  * (1-ratio) + b.blueF()  * ratio,
        a.alphaF() * (1-ratio) + b.alphaF() * ratio
    );
}


/**
 * \brief Get an insertion point in the gradient
 * \param gradient  Gradient stops to look into (must be properly set up)
 * \param factor    Value in [0, 1] to get the color for
 * \return A pair whose first element is the index to insert the new value at, and a GradientStop
 */
inline QPair<int, QGradientStop> Q_DECL_EXPORT gradientBlendedColorInsert(const QGradientStops& gradient, qreal factor)
{
    if ( gradient.empty() )
        return {0, {0, QColor()}};

    if ( gradient.size() == 1 || factor <= 0 )
        return {0, gradient.front()};

    int i = 0;
    QGradientStop s1;
    for ( auto s2 : gradient )
    {
        if ( factor < s2.first )
        {
            qreal ratio = (factor - s1.first) / (s2.first - s1.first);
            return {i, {factor, blendColors(s1.second, s2.second, ratio)}};
        }
        s1 = s2;
        ++i;
    }

    return {gradient.size(), gradient.back()};
}

/**
 * \brief Returns a color in the gradient
 * \param gradient  Gradient stops to look into (must be properly set up)
 * \param factor    Value in [0, 1] to get the color for
 */
inline QColor Q_DECL_EXPORT gradientBlendedColor(const QGradientStops& gradient, qreal factor)
{
    return gradientBlendedColorInsert(gradient, factor).second.second;
}

/**
 * \brief Returns a color in the gradient
 * \param gradient  Gradient to look into
 * \param factor    Value in [0, 1] to get the color for
 */
inline QColor Q_DECL_EXPORT gradientBlendedColor(const QGradient& gradient, qreal factor)
{
    return gradientBlendedColor(gradient.stops(), factor);
}



#endif // GRADIENT_EDITOR_H


