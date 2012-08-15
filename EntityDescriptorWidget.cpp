/*  This file is part of [To be named], a STEP-Express viewer
    Copyright (C) 2012 Laurent Bauer lahoraent@hotmail.com

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; version 2
    of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "EntityDescriptorWidget.h"
#include "ui_EntityDescriptorWidget.h"

#include <iostream>
using namespace std;

EntityDescriptorWidget::EntityDescriptorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityDescriptorWidget)
{
    ui->setupUi(this);
    connect (ui->attrListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(findEntityDescriptor(QListWidgetItem*)));
    connect (ui->typeListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(findEntityDescriptor(QListWidgetItem*)));
    connect (ui->attrListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(findEntityDescriptor(QListWidgetItem*)));
}

EntityDescriptorWidget::~EntityDescriptorWidget()
{
    delete ui;
}

void EntityDescriptorWidget::fill(EntityDescriptor *ed)
{
    QListWidget * attrListWidget = ui->attrListWidget;
    QListWidget * typeListWidget = ui->typeListWidget;
    attrListWidget->clear();
    typeListWidget->clear();
    ui->nameLineEdit->setText(QString(ed->Name()));

    // adapted from clprobe-ui/stepentdescriptor.cc
    const AttrDescriptorList * attrList = &( ( ( EntityDescriptor * )ed )->ExplicitAttr() );

    int attrCount = attrList->EntryCount();
    cout << "-----------------------------" << endl;
    cout << "attr entries =" << attrCount << endl;

    std::string str;

    AttrDescLinkNode * attrPtr = ( AttrDescLinkNode * )attrList->GetHead();
    while( attrPtr != 0 ) {
        str.clear();

        const AttrDescriptor * ad = attrPtr->AttrDesc();
/*
        if( ad->Derived() == LTrue ) {
            str.append( "<" );
        }
        std::string tmp;
        str.append( ad->AttrExprDefStr( tmp ) );
        if( ad->Derived() == LTrue ) {
            str.append( ">" );
        }
        */
        str.append(ad->Name());
        str.append(" : ");
        str.append(ad->TypeName());

        QString attrText = str.c_str();
        QListWidgetItem * item = new QListWidgetItem(attrText,ui->attrListWidget);
        ui->attrListWidget->addItem(item);

        // tests
        // BUG SCL: ad->BaseTypeDescriptor() : .cpp undefined
        cout << "baseType =" << ad->BaseType() << endl;
        cout << "Type =" << ad->Type() << endl;
        cout << "Type->Name =" << ad->TypeName() << endl;
        cout << "DomainType->Name =" << ad->DomainType()->Name() << endl;
        cout << "NonRefType->Name =" << ad->NonRefTypeDescriptor()->Name() << endl;
        cout << "ReferentType->Name =" << ad->ReferentType()->Name() << endl;
        cout << "Type->Name =" << ad->Type() << endl;


        const EntityDescriptor * attrEd = dynamic_cast<const EntityDescriptor *> (ad->ReferentType() );
        if (attrEd)
        {
            // store the EntityDescriptor
            void* voidAttrEd=(void*) attrEd;
            item->setData(Qt::UserRole,QVariant::fromValue(voidAttrEd) );
            item->setIcon(QIcon(":/type"));
        }
        else
            item->setIcon(QIcon(":/attribute"));

        // cout << str << endl;
        attrPtr = ( AttrDescLinkNode * )attrPtr->NextNode();
    }


    // types
    const EntityDescriptorList * subtypeList = &( ( ( EntityDescriptor * )ed )->Subtypes() );
    int subTypeCount = subtypeList->EntryCount();
    cout << "sub type entries =" << subTypeCount << endl;
    EntityDescLinkNode * subtypePtr =
        ( EntityDescLinkNode * )subtypeList->GetHead();
    while( subtypePtr != 0 ) {
        str.clear();
        str.append(subtypePtr->EntityDesc()->Name());
        QString subTypeText = str.c_str();

        QListWidgetItem * item = new QListWidgetItem(subTypeText,typeListWidget);
        typeListWidget->addItem(item);

        EntityDescriptor * subTypeEd = subtypePtr->EntityDesc();
        // store the EntityDescriptor
        void* voidSubTypeEd=(void*) subTypeEd;
        item->setData(Qt::UserRole,QVariant::fromValue(voidSubTypeEd) );
        item->setIcon(QIcon(":/type"));

        subtypePtr = ( EntityDescLinkNode * )subtypePtr->NextNode();
    }


}

void EntityDescriptorWidget::findEntityDescriptor(QListWidgetItem * item)
{
    //  MOCHE
    EntityDescriptor * desc = (EntityDescriptor *) item->data(Qt::UserRole).value<void*>();
    if (desc)
        emit entityDescriptorDoubleClicked(desc);
}
