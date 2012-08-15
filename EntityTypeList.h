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

#ifndef ENTITYTYPELIST_H
#define ENTITYTYPELIST_H

#include <QListWidget>
#include <QHash>
#include <scl_cf.h>
extern void SchemaInit( class Registry & );
//#include <STEPfile.h>
#include <sdai.h>
#include <STEPattribute.h>
#include <SdaiAUTOMOTIVE_DESIGN.h>

class EntityTypeList : public QListWidget
{
    Q_OBJECT
public:
    explicit EntityTypeList(QWidget *parent = 0);
    
signals:
    void entityChanged(const EntityDescriptor *);

public slots:
    void findEntity();
    void select( const EntityDescriptor *ed);

private:
//    bool strict;
    Registry  registry;
//    InstMgr   instance_list;
//    STEPfile  sfile;
    QHash <const void*, QListWidgetItem*> m_EntityDescriptorToItem;
    QIcon m_EntityIcon;
};

#endif // ENTITYTYPELIST_H
