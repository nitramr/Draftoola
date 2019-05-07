#ifndef LAYOUTSEGMENT_H
#define LAYOUTSEGMENT_H

#include <QWidget>
#include <QLayout>

class LayoutSegment : public QWidget
{
private:
	QGridLayout * m_layout;

public:
    LayoutSegment(QWidget *parent = nullptr);
	void addWidget(QWidget * item, int row, int column);
	void addGridLayout(QGridLayout*gridLayout);
	QGridLayout *getLayout();
};

#endif // LAYOUTSEGMENT_H
