#ifndef STROKE_H
#define STROKE_H


#include <QColor>
#include <QString>
#include <QPen>

#include "itemstruct.h"

class Stroke : public QPen
{
public:

	Stroke(const QString name, Qt::PenStyle style);
	Stroke(const QString name, const QColor & color);
	Stroke(const QString name, const QBrush & brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin);
	Stroke(const QString name, const QPen & pen);

	// Properties
	QString name() const;


private:
	QString m_name;

};

#endif // STROKE_H
