#ifndef FILLS_H
#define FILLS_H


#include <QColor>
#include <QBrush>
#include "itemstruct.h"

class Fills : public QBrush
{
public:

	Fills(const QString name);
	Fills(const QString name, Qt::BrushStyle style);
	Fills(const QString name, const QColor & color, Qt::BrushStyle style = Qt::SolidPattern);
	Fills(const QString name, Qt::GlobalColor color, Qt::BrushStyle style = Qt::SolidPattern);
	Fills(const QString name, const QColor & color, const QPixmap & pixmap);
	Fills(const QString name, Qt::GlobalColor color, const QPixmap & pixmap);
	Fills(const QString name, const QPixmap & pixmap);
	Fills(const QString name, const QImage & image);
	Fills(const QString name, const QBrush & other);
	Fills(const QString name, const QGradient & gradient);

	// Properties
	QString name();


private:
	QString m_name;

};

#endif // FILLS_H
