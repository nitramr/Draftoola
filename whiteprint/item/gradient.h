#ifndef GRADIENT_H
#define GRADIENT_H


#include <QString>

#include "itemstruct.h"

class Gradient
{
public:
	Gradient(QString name);

	// Properties
	void setType(GradientType type);
	GradientType type();
	void setName(QString name);
	QString name();

private:
	GradientType m_type;
	QString m_name;

};

#endif // GRADIENT_H
