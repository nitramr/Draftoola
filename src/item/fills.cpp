#include "fills.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Fills::Fills() : Fills(QString::null){}

Fills::Fills(const QString name) : Fills(name, QColor(Qt::white)){}

Fills::Fills(const QString name, const QColor &color, const Qt::BrushStyle style) : AbstractItemProperty(name){
    m_gradient = QLinearGradient(0,0,100,100);
    setColor(color);
    m_style = style;
    m_fillMode = FillMode::Fill;
}

Fills::Fills(const QString name, const QPixmap &pixmap, const FillMode fillMode) :  Fills(name, QColor(Qt::white)){
    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const QImage &image, const FillMode fillMode) : Fills(name, QColor(Qt::white)){

	QPixmap pixmap(image.size());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.drawImage(0,0,image);
	painter.end();

    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const QGradient &gradient) : Fills(name, QColor(Qt::white)){
	setGradient(gradient);
}

Fills::Fills(const Fills &other)
{    
    m_id = other.m_id;
        m_name = other.m_name;
        m_fillType = other.m_fillType;
        m_fillMode = other.m_fillMode;
        m_gradient = other.m_gradient;
        m_color = other.m_color;
       m_pixmap = other.m_pixmap;
        m_style = other.m_style;
        m_blendMode = other.m_blendMode;
        m_opacity = other.m_opacity;
        m_isOn = other.m_isOn;

}

bool Fills::operator==(const Fills &other) const
{
    return m_id == other.m_id &&
    m_name == other.m_name &&
    m_fillType == other.m_fillType &&
    m_fillMode == other.m_fillMode &&
    m_gradient == other.m_gradient &&
    m_color == other.m_color &&
   // m_pixmap == other.m_pixmap &&
    m_style == other.m_style &&
    m_blendMode == other.m_blendMode &&
    m_opacity == other.m_opacity &&
    m_isOn == other.m_isOn;
}

QDebug operator<<(QDebug dbg, const Fills &fills)
{
    int fType = QVariant::fromValue(fills.fillType()).value<int>();
    int fMode = QVariant::fromValue(fills.fillMode()).value<int>();

    dbg << "Fills( ID:" << fills.ID() <<
           ", Name:" << fills.name() <<
           ", FillType:" << fType <<
           ", FillMode:" << fMode <<
           ", Gradient:" << fills.gradient() <<
           ", Color:" << fills.color() <<
           ", Pixmap:" << fills.pixmap() <<
           ", Style:" << fills.style() <<
           ", BlendMode:" << fills.blendMode() <<
           ", Opacity:" << fills.opacity() <<
           ", IsOn:" << fills.isOn() <<
           ")";
    return dbg.maybeSpace();
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

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
    int opacity = qRound(color.alpha() / 2.56);
    setOpacity(opacity);

    if(color.alpha() < 255) color.setAlpha(255);

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

void Fills::setOpacity(int opacity)
{
    opacity = qMax(0, qMin(100, opacity)); //clamp values
    m_opacity = opacity;
}

int Fills::opacity() const
{
    return m_opacity;
}
