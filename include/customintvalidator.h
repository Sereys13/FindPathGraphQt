#ifndef CUSTOMINTVALIDATOR_H
#define CUSTOMINTVALIDATOR_H

#include <QIntValidator>
#include <QString>
#include <QRegularExpression>


class CustomIntValidator : public QIntValidator
{
public:
    CustomIntValidator(QObject* parent);
    CustomIntValidator(int bottom, int top, QObject *parent = nullptr);
    void fixup(QString& input) const override;

};

#endif // CUSTOMINTVALIDATOR_H
