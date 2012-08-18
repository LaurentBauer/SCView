#include "ExpressTextEdit.h"
#include <ExpDict.h>

ExpressTextEdit::ExpressTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
}

void ExpressTextEdit::setEntityDescriptor(const EntityDescriptor *entityDescriptor)
{
    clear();
    std::string str;
    QString text(entityDescriptor->GenerateExpress(str));
    setPlainText(text);
}

void ExpressTextEdit::setTypeDescriptor(const TypeDescriptor *typeDescriptor)
{
    clear();
    std::string str;
    QString text(typeDescriptor->GenerateExpress(str));
    setPlainText(text);
}
