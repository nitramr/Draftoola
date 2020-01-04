#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QStyle>
#include <QStyleOption>
#include <QStylePainter>

class ButtonGroupButton : public QToolButton
{
    Q_OBJECT
public:

    enum Type{
        normal = 0,
        left = 1,
        middle = 2,
        right = 3
    };
    Q_ENUM(Type)

    ButtonGroupButton(QWidget *parent = nullptr);

    void setButtonType(ButtonGroupButton::Type type);
    ButtonGroupButton::Type buttonType();

    void setData(QVariant data);
    QVariant data();

    void paintEvent(QPaintEvent *event);

protected:
//    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget);

private:
    ButtonGroupButton::Type m_type;
    QVariant m_data;

};


class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    ButtonGroup(QWidget *parent = nullptr);

    QToolButton *createButton(QString const& name,bool checked,QString const& sheet = QString());

    void addButton(ButtonGroupButton *button, bool checked);

    QAbstractButton * checkedButton() const;
    QList<QAbstractButton *> buttons() const;

signals:
    void buttonClicked(QAbstractButton * button);
    void buttonPressed(QAbstractButton * button);

private:
    QButtonGroup *bg;
    QHBoxLayout *hl;
};

#endif // BUTTONGROUP_H
