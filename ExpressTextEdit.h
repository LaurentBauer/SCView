#ifndef EXPRESSTEXTEDIT_H
#define EXPRESSTEXTEDIT_H

#include <QTextEdit>

class EntityDescriptor;
class TypeDescriptor;

class ExpressTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ExpressTextEdit(QWidget *parent = 0);

signals:
    
public slots:
    void setEntityDescriptor(const EntityDescriptor * entityDescriptor);
    void setTypeDescriptor(const TypeDescriptor * typeDescriptor);

};

#endif // EXPRESSTEXTEDIT_H
