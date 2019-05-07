#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QButtonGroup>

class ButtonGroupButton : public QToolButton
{
    Q_OBJECT
public:

    enum class Type{
        normal = 0,
        left = 1,
        middle = 2,
        right = 3
    };
    Q_ENUM(Type)

    ButtonGroupButton(QWidget *parent = nullptr);

    void setButtonType(ButtonGroupButton::Type type);
    ButtonGroupButton::Type buttonType();

    void paintEvent(QPaintEvent *event);

private:
    ButtonGroupButton::Type m_type;

};


class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    ButtonGroup(QWidget *parent = nullptr);

    QToolButton *createButton(QString const& name,bool checked,QString const& sheet = QString());

    void addButton(ButtonGroupButton *button, bool checked);

private:
    QButtonGroup *bg;
    QHBoxLayout *hl;
};

#endif // BUTTONGROUP_H
