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

#include "ExpressGScene.h"
#include "EntityItem.h"

#include <iostream>
using namespace std;

ExpressGScene::ExpressGScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

QGraphicsItem *ExpressGScene::setEntityDescriptor(const EntityDescriptor *ed)
{
    this->clear();
    EntityItem * edItem = new EntityItem(ed);
    edItem->setPos(0.0,0.0);
    addItem(edItem);
    return edItem;
}

void ExpressGScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (!selectedItems().isEmpty())
    {
        QGraphicsItem * selItem = selectedItems().first();
        EntityItem * entityItem = qgraphicsitem_cast <EntityItem *> (selItem);
        if (entityItem!=0)
        {
            cout << " ExpressGScene::mouseDoubleClickEvent" << endl;
            emit entityDescriptorDoubleClicked( entityItem->entityDescriptor() );
        }

    }
}

