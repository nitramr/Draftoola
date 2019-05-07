#ifndef INTELLIGENTSPINBOX_H
#define INTELLIGENTSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLineEdit>

class IntelligentSpinBox : public QDoubleSpinBox
{
public:
    IntelligentSpinBox(QWidget *parent = nullptr);

private:
    double dbl_value;
    QString str_value;
    QLineEdit *lineEdit;
    QRegExpValidator *validator;

protected:
    QValidator::State validate(QString &text, int &pos) const;
    double valueFromText(const QString &text) const;
};

#endif // INTELLIGENTSPINBOX_H
