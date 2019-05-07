#ifndef STYLEFACTORY_H
#define STYLEFACTORY_H

#include <QProxyStyle>
#include <QPalette>

class StyleFactory : public QProxyStyle
{
    Q_OBJECT
public:
    StyleFactory(const QString name);

    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const override;

    void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option,
                            QPainter *painter, const QWidget *widget = nullptr) const override;

};

#endif // STYLEFACTORY_H
