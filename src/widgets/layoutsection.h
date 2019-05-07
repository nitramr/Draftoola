#ifndef LAYOUTSECTION_H
#define LAYOUTSECTION_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include "flowlayout.h"

class LayoutSectionHeader : public QWidget
{
	Q_OBJECT

//friend class LayoutSection;

public:
    LayoutSectionHeader(QString text, QWidget *menu = nullptr, bool toggle = false, QWidget *parent = nullptr);
    void addButton(QToolButton *button);
    void removeButton(QToolButton *button);
    void setCollapsed(bool isCollapsed);

private:
	void paintEvent(QPaintEvent *);
    QHBoxLayout *m_headerLayout;
	QLabel *m_caption;
    QToolButton *m_btnMenu;
    QToolButton *m_btnCollapse;
    bool m_collapsed;   

signals:
    void sendCollapsedState(bool);

private slots:
    void setCollapsedState();
};


class LayoutSection : public QWidget
{
	Q_OBJECT
public:
    LayoutSection(QString text, QWidget *menu = nullptr, bool toggle = false, QWidget *parent = nullptr);
	void addWidget(QWidget * item);
    void addButton(QToolButton *button);
    void removeButton(QToolButton *button);

private:
    QVBoxLayout *m_flowLayout;
    LayoutSectionHeader * m_header;
    QWidget * m_drawer;

signals:
    void collapsedState(bool);

public slots:
    void setCollapsedState(bool);
};

#endif // LAYOUTSECTION_H
