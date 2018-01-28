#ifndef STROKE_H
#define STROKE_H


#include <QColor>
#include <QString>
#include <QPen>

#include "itemstruct.h"

class Stroke : public QPen
{
public:

	Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition = StrokePosition::Inner);
	Stroke(const QString name, const QColor & color, const StrokePosition strokePosition = StrokePosition::Inner);
	Stroke(const QString name, const QBrush & brush, qreal width, const StrokePosition strokePosition = StrokePosition::Inner, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::MiterJoin);
	Stroke(const QString name, const QPen & pen, const StrokePosition strokePosition = StrokePosition::Inner);

	// Properties
	QString name() const;
	void setStrokePosition(StrokePosition position);
	StrokePosition strokePosition() const;



private:
	QString m_name;
	StrokePosition m_strokePosition;

};

#endif // STROKE_H
