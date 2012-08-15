/********************************************************************************
** Form generated from reading UI file 'EntityDescriptorWidget.ui'
**
** Created: Wed 8. Aug 16:56:54 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTITYDESCRIPTORWIDGET_H
#define UI_ENTITYDESCRIPTORWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntityDescriptorWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *nameLineEdit;
    QSplitter *splitter;
    QListWidget *attrListWidget;
    QListWidget *typeListWidget;

    void setupUi(QWidget *EntityDescriptorWidget)
    {
        if (EntityDescriptorWidget->objectName().isEmpty())
            EntityDescriptorWidget->setObjectName(QString::fromUtf8("EntityDescriptorWidget"));
        EntityDescriptorWidget->resize(592, 300);
        verticalLayout = new QVBoxLayout(EntityDescriptorWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(EntityDescriptorWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        nameLineEdit = new QLineEdit(EntityDescriptorWidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(nameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(EntityDescriptorWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        attrListWidget = new QListWidget(splitter);
        attrListWidget->setObjectName(QString::fromUtf8("attrListWidget"));
        splitter->addWidget(attrListWidget);
        typeListWidget = new QListWidget(splitter);
        typeListWidget->setObjectName(QString::fromUtf8("typeListWidget"));
        splitter->addWidget(typeListWidget);

        verticalLayout->addWidget(splitter);


        retranslateUi(EntityDescriptorWidget);

        QMetaObject::connectSlotsByName(EntityDescriptorWidget);
    } // setupUi

    void retranslateUi(QWidget *EntityDescriptorWidget)
    {
        EntityDescriptorWidget->setWindowTitle(QApplication::translate("EntityDescriptorWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EntityDescriptorWidget", "name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EntityDescriptorWidget: public Ui_EntityDescriptorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTITYDESCRIPTORWIDGET_H
