#ifndef FILLS_H
#define FILLS_H

#include <QBrush>
#include <QGradient>
#include <QPixmap>
#include <QColor>
#include <QLinearGradient>
#include <QPainter>
#include "itemstruct.h"

class Fills
{
public:

	Fills(const QString name);
	Fills(const QString name, const QColor & color, const Qt::BrushStyle style = Qt::SolidPattern);
	Fills(const QString name, const QColor & color, const QPixmap & pixmap, const FillMode fillMode = FillMode::Fill);
	Fills(const QString name, const QPixmap & pixmap);
	Fills(const QString name, const QImage & image);
	Fills(const QString name, const QGradient & gradient);

	// Properties
	QString name();

	void setFillType(FillType filltype);
	FillType fillType() const;

	void setFillMode(FillMode fillMode);
	FillMode fillMode() const;

	void setGradient(QGradient gradient);
	virtual QGradient gradient() const;

	void setColor(QColor color);
	QColor color() const;

	void setPixmap(QPixmap pixmap);
	QPixmap pixmap() const;

	void setStyle(Qt::BrushStyle style);
	Qt::BrushStyle style() const;

	void setBlendMode(QPainter::CompositionMode compositionMode);
	QPainter::CompositionMode blendMode() const;

private:
	QString m_name;
	FillType m_fillType = FillType::Color;
	FillMode m_fillMode = FillMode::Fill;
	QGradient m_gradient;
	QColor m_color;
	QPixmap m_pixmap;
	Qt::BrushStyle m_style;
	QPainter::CompositionMode m_blendMode;


};

#endif // FILLS_H
