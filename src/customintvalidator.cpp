#include "customintvalidator.h"

CustomIntValidator::CustomIntValidator(QObject* parent) : QIntValidator(parent)
{
}

CustomIntValidator::CustomIntValidator(int bottom, int top, QObject* parent) : QIntValidator(bottom, top, parent){
}


void CustomIntValidator::fixup(QString &input) const {
    QRegularExpression regex("^0+(?!$)");
    input = input.trimmed().remove(regex);
    QIntValidator::fixup(input);
}
