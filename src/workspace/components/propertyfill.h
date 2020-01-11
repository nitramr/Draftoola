#ifndef PROPERTYFILL_H
#define PROPERTYFILL_H

#include <QWidget>
#include <QPixmap>

#include <fills.h>

namespace Ui {
class propertyFill;
}

class PropertyFill : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyFill(QWidget *parent = nullptr);
    explicit PropertyFill(Fills fill, QWidget *parent = nullptr);
    ~PropertyFill();

    void setFill(Fills fill);
    Fills fill() const;

private:
    Ui::propertyFill *ui;

    Fills m_fill;

    void drawFill(Fills fill);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateFill();

signals:
    void hasChanged(bool);

};

#endif // PROPERTYFILL_H
