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

#ifndef ENTITYTYPELIST_H
#define ENTITYTYPELIST_H

#include <QTreeWidget>
#include <QHash>
#include <QString>
class Registry;
class TypeDescriptor;

class QStringListModel;

// EntityTypeList : actually is the EntityDescriptorList... should be renamed
class SchemaTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SchemaTree(Registry * registry, QWidget *parent = 0);
    void fillStringListModel(QStringListModel * model);

signals:
    void selectedDescriptorChanged(const TypeDescriptor *);

public slots:
    void findSelection();
    void select( const TypeDescriptor *td);

private:
    Registry * m_Registry;
    QHash <const void*, QTreeWidgetItem*> m_DescriptorToItem;
    QIcon m_EntityIcon;
    QIcon m_TypeIcon;
};

#endif // ENTITYTYPELIST_H
