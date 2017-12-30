#include "gradient.h"

Gradient::Gradient(QString name)
{
	m_type = GradientType::Linear;
	m_name = name;
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Gradient::setType(GradientType type){
	m_type = type;
}

GradientType Gradient::type(){
	return m_type;
}

void Gradient::setName(QString name){
	m_name = name;
}

QString Gradient::name(){
	return m_name;
}
