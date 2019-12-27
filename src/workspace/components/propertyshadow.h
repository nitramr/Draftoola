#ifndef PROPERTYSHADOW_H
#define PROPERTYSHADOW_H

#include <QWidget>
#include <QPixmap>
#include "src/item/shadow.h"

namespace Ui {
class propertyShadow;
}

class PropertyShadow : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyShadow(QWidget *parent = nullptr);
    explicit PropertyShadow(Shadow shadow, QWidget *parent = nullptr);
    ~PropertyShadow();

    void setShadow(Shadow shadow);
    Shadow shadow() const;

private:
    Ui::propertyShadow *ui;

    Shadow m_shadow;
    QPixmap m_colorPreview;

    void drawShadow(Shadow shadow);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateShadow();

signals:
    void hasChanged(bool);
};

#endif // PROPERTYSHADOW_H
