/*  This file is part of SCView, a STEP-Express viewer
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

#include "SchemaTree.h"
#include <QStringListModel>
#include <ExpDict.h>
#include <Registry.h>

#include <iostream>
using namespace std;

enum itemType {
    EntityDescriptorItemType
    , TypeDescriptorItemType
    };


SchemaTree::SchemaTree(Registry *registry, QWidget *parent)
    : QTreeWidget(parent)
    , m_Registry( registry )
    , m_EntityIcon(":/Entity")
    , m_TypeIcon(":/Type")
{

    // L&F
    setAlternatingRowColors(true);
    setHeaderHidden(true);

    // Root : The Schema
    m_Registry->ResetSchemas();
    const Schema * schema = m_Registry->NextSchema();
    QTreeWidgetItem * rootItem = new QTreeWidgetItem (this);
    rootItem->setText(0, schema->Name());
    rootItem->setIcon(0, QIcon(":/Schema"));


    //Fill Entities
    // Root for Entities
    QTreeWidgetItem * entitiesItem = new QTreeWidgetItem (rootItem);
    entitiesItem->setText(0,tr("Entities") );
    entitiesItem->setIcon(0, m_EntityIcon);
    // all entities
    const EntityDescriptor * entityDescriptor;
    while ( (entityDescriptor= m_Registry->NextEntity() ) )
    {
        QTreeWidgetItem * entityItem = new QTreeWidgetItem(entitiesItem, EntityDescriptorItemType);
        entityItem->setText(0,entityDescriptor->Name());
        entityItem->setIcon(0,m_EntityIcon);
        void* voidEntityDescriptor=(void*) entityDescriptor;
        entityItem->setData(0,Qt::UserRole,QVariant::fromValue(voidEntityDescriptor) );
        m_DescriptorToItem.insert(voidEntityDescriptor, entityItem);
    }

    //Fill Types
    // Root for types
    QTreeWidgetItem * typesItem = new QTreeWidgetItem (rootItem);
    typesItem->setText(0,tr("Types") );
    typesItem->setIcon(0, m_TypeIcon);
    // all types
    const TypeDescriptor * typeDescriptor;
    while ( (typeDescriptor= m_Registry->NextType() ) )
    {
        QTreeWidgetItem * typeItem = new QTreeWidgetItem(typesItem, TypeDescriptorItemType);
        typeItem->setText(0,typeDescriptor->Name());
        typeItem->setIcon (0,m_TypeIcon);
        void* voidTypeDescriptor=(void*) typeDescriptor;
        typeItem->setData(0,Qt::UserRole,QVariant::fromValue(voidTypeDescriptor) );
        m_DescriptorToItem.insert(voidTypeDescriptor, typeItem);
    }

    sortItems(0,Qt::AscendingOrder);
    connect (this, SIGNAL(itemSelectionChanged()), this, SLOT(findSelection()));
}

void SchemaTree::fillStringListModel(QStringListModel *model)
{
    QHash <const void*, QTreeWidgetItem*>::const_iterator it ;
    QStringList list;
    for (it = m_DescriptorToItem.constBegin(); it != m_DescriptorToItem.constEnd(); ++it)
        list << it.value()->text(0);
    model->setStringList(list);
}

void SchemaTree::findSelection()
{
    if (selectedItems().count()>0)
    {
        QTreeWidgetItem * item = selectedItems().first();
        int itemType = item->type();
        if ((itemType==EntityDescriptorItemType) || (itemType==TypeDescriptorItemType) )
        {
            TypeDescriptor * desc = (TypeDescriptor *) item->data(0,Qt::UserRole).value<void*>();
            if (desc)
                emit selectedDescriptorChanged(desc);
        }
    }
}

void SchemaTree::select(const TypeDescriptor *td)
{
    blockSignals(true);
    if (m_DescriptorToItem.contains(td))
    {
        clearSelection();
        QTreeWidgetItem * item = m_DescriptorToItem.value(td);
        item->setSelected(true);
        if (selectedItems().size() >0)
            scrollToItem(selectedItems().at(0));
    }
    blockSignals(false);
}

