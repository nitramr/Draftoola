#include "fills.h"

Fills::Fills(const QString name) : QBrush(), m_name(name){}
Fills::Fills(const QString name, Qt::BrushStyle brushStyle) : QBrush(brushStyle), m_name(name){}
Fills::Fills(const QString name, const QColor &color, Qt::BrushStyle style) : QBrush(color, style), m_name(name){}
Fills::Fills(const QString name, Qt::GlobalColor color, Qt::BrushStyle style) :QBrush(color, style), m_name(name){}
Fills::Fills(const QString name, const QColor &color, const QPixmap &pixmap) : QBrush(color, pixmap), m_name(name){}
Fills::Fills(const QString name, Qt::GlobalColor color, const QPixmap &pixmap) : QBrush(color, pixmap), m_name(name){}
Fills::Fills(const QString name, const QPixmap &pixmap) :  QBrush(pixmap), m_name(name){}
Fills::Fills(const QString name, const QImage &image) : QBrush(image), m_name(name){}
Fills::Fills(const QString name, const QBrush &other) : QBrush(other), m_name(name){}
Fills::Fills(const QString name, const QGradient &gradient) : QBrush(gradient), m_name(name){}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

QString Fills::name(){
	return m_name;
}
