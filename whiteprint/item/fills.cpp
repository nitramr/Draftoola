#include "fills.h"

Fills::Fills(const QString name) : Fills(name, QColor(Qt::white)){}

Fills::Fills(const QString name, const QColor &color, const Qt::BrushStyle style) : m_name(name){
	setGradient(QLinearGradient(0,0,100,100));
	setColor(color);
	setStyle(style);
	setBlendMode(QPainter::CompositionMode_Source);
}

Fills::Fills(const QString name, const QColor &color, const QPixmap &pixmap, const FillMode fillMode) : Fills(name, color){
	setPixmap(pixmap);
	setFillMode(fillMode);
}

Fills::Fills(const QString name, const QPixmap &pixmap) :  Fills(name, QColor(Qt::transparent), pixmap){}

Fills::Fills(const QString name, const QImage &image) : Fills(name, QColor(Qt::transparent)){

	QPixmap pixmap(image.size());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.drawImage(0,0,image);
	painter.end();

	setPixmap(pixmap);
}

Fills::Fills(const QString name, const QGradient &gradient) : Fills(name){
	setGradient(gradient);
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QString Fills::name(){
	return m_name;
}

void Fills::setFillType(FillType filltype)
{
	m_fillType = filltype;
}

FillType Fills::fillType() const
{
	return m_fillType;
}

void Fills::setFillMode(FillMode fillMode)
{
	m_fillMode = fillMode;
}

FillMode Fills::fillMode() const
{
	return m_fillMode;
}

void Fills::setGradient(QGradient gradient)
{
	m_gradient = gradient;
	setFillType(FillType::Gradient);
}

QGradient Fills::gradient() const
{
	return m_gradient;
}

void Fills::setColor(QColor color)
{
	m_color = color;
	setFillType(FillType::Color);
}

QColor Fills::color() const
{
	return m_color;
}

void Fills::setPixmap(QPixmap pixmap)
{
	m_pixmap = pixmap;
	setFillType(FillType::Image);
}

QPixmap Fills::pixmap() const
{
	return m_pixmap;
}

void Fills::setStyle(Qt::BrushStyle style)
{
	m_style = style;
}

Qt::BrushStyle Fills::style() const
{
	return m_style;
}

void Fills::setBlendMode(QPainter::CompositionMode compositionMode)
{
	m_blendMode = compositionMode;
}

QPainter::CompositionMode Fills::blendMode() const
{
	return m_blendMode;
}
