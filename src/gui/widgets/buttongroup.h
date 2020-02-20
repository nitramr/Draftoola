/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

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

    QWidget *createButton(QString const& name,bool checked,QString const& sheet = QString());

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
