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

#include "EntityTypeList.h"

#include <iostream>
using namespace std;

EntityTypeList::EntityTypeList(QWidget *parent)
    : QListWidget(parent)
    , registry( SchemaInit )
    , m_EntityIcon(":/type")
{
    // L&F
    setAlternatingRowColors(true);

    //Fill
    const EntityDescriptor * entityDescriptor;
    while ( (entityDescriptor= registry.NextEntity() ) )
    {
        QString entityName = entityDescriptor->Name();
        QListWidgetItem * entityItem = new QListWidgetItem(m_EntityIcon, entityName, this);
        void* voidEntityDescriptor=(void*) entityDescriptor;
        entityItem->setData(Qt::UserRole,QVariant::fromValue(voidEntityDescriptor) );
        addItem(entityItem);
        m_EntityDescriptorToItem.insert(voidEntityDescriptor, entityItem);
    }
    sortItems();

    connect (this, SIGNAL(itemSelectionChanged()), this, SLOT(findEntity()));
}

void EntityTypeList::findEntity()
{
    if (selectedItems().count()>0)
    {
        QListWidgetItem * item = selectedItems().first();

        //  MOCHE
        EntityDescriptor * desc = (EntityDescriptor *) item->data(Qt::UserRole).value<void*>();
        if (desc)
            emit entityChanged(desc);

    }
}

void EntityTypeList::select(const EntityDescriptor *ed)
{
    cout << "EntityTypeList::select : " << ed->Name() << endl;
    if (m_EntityDescriptorToItem.contains(ed))
    {
        clearSelection();
        QListWidgetItem * item = m_EntityDescriptorToItem.value(ed);
        item->setSelected(true);
        if (selectedItems().size() >0)
            scrollToItem(selectedItems().at(0));
    }
}
