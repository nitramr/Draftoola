#ifndef FILLS_H
#define FILLS_H

#include <QBrush>
#include <QGradient>
#include <QPixmap>
#include <QColor>
#include <QLinearGradient>
#include <QPainter>
#include "itemstruct.h"
#include "abstractitemproperty.h"

class Fills : public AbstractItemProperty
{

//    Q_GADGET
public:

    // Constructor
    Fills();
    Fills(const QString name);
    Fills(const QString name, const QColor & color, const Qt::BrushStyle style = Qt::SolidPattern);
    Fills(const QString name, const QPixmap & pixmap, const FillMode fillMode = FillMode::Fill);
    Fills(const QString name, const QImage & image, const FillMode fillMode = FillMode::Fill);
    Fills(const QString name, const QGradient & gradient);
    Fills(const Fills &other);
    virtual ~Fills(){}

    bool operator==( const Fills & other ) const;
    inline bool operator!=(const Fills &fill) const { return !(operator==(fill)); }

	// Properties
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

    void setOpacity(int opacity);
    int opacity() const;

private:    

	FillType m_fillType = FillType::Color;
	FillMode m_fillMode = FillMode::Fill;
	QGradient m_gradient;
	QColor m_color;
    QPixmap m_pixmap;
	Qt::BrushStyle m_style;
    int m_opacity;


};
Q_DECLARE_METATYPE(Fills)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Fills &fills);
#endif

#endif // FILLS_H
