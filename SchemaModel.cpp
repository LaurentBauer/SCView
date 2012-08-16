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

#include "SchemaModel.h"

#include <iostream>
using namespace std;

SchemaModel::SchemaModel()
    :strict(false)
    , registry( SchemaInit )
    , instance_list()
    , sfile( registry, instance_list, "", strict )
{
    /*
    const EntityDescriptor * entityDescriptor;
    while ( (entityDescriptor= registry.NextEntity() ) )
    {
        cout << entityDescriptor->Name() << endl;
    }
*/
    const TypeDescriptor * typeDescriptor;
    while ( (typeDescriptor= registry.NextType() ) )
    {
        cout << typeDescriptor->Name() << endl;
    }

}
