#ifndef PROPERTYEXPORTLEVEL_H
#define PROPERTYEXPORTLEVEL_H

#include <QWidget>
#include <QToolButton>

#include <exportlevel.h>

namespace Ui {
class propertyExportLevel;
}

class PropertyExportLevel : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyExportLevel(QWidget *parent = nullptr);
    explicit PropertyExportLevel(ExportLevel exportLevel, QWidget *parent = nullptr);
    ~PropertyExportLevel();

    void setExportLevel(ExportLevel exportLevel);
    ExportLevel exportLevel() const;

private:
    Ui::propertyExportLevel *ui;

    ExportLevel m_exportLevel;

    void drawFill(ExportLevel exportLevel);
    void connectSlots();
    void disconnectSlots();

signals:
    void remove(PropertyExportLevel*);
    void hasChanged(bool);

private slots:
    void removeClick();
    void updateFill();

};

#endif // PROPERTYEXPORTLEVEL_H
