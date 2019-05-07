#ifndef GRADIENT_H
#define GRADIENT_H


#include <QString>
#include <QDebug>

#include "itemstruct.h"
#include "abstractitemproperty.h"

class Gradient : public AbstractItemProperty
{
 //   Q_GADGET
public:
    Gradient();
    Gradient(QString name, GradientType type = GradientType::Linear);
    Gradient(const Gradient &other);
    ~Gradient(){}

    bool operator==( const Gradient & other ) const;
    inline bool operator!=(const Gradient &gradient) const { return !(operator==(gradient)); }

	// Properties
	void setType(GradientType type);
    GradientType type() const;

private:
	GradientType m_type;

};
Q_DECLARE_METATYPE(Gradient)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Gradient &gradient);
#endif

#endif // GRADIENT_H
